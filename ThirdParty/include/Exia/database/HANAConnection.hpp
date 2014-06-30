#pragma once
#include <string>
#include <memory>
#include "HANAEnvironment.hpp"
#include "HANAStatement.hpp"
#include "HANACallableStatement.hpp"
#include "HANAPreparedStatement.hpp"

namespace db
{
	enum ConnectionStatus
	{
		Opened,
		Closed
	};
	static HANAEnvironment HANAEnv;
	class HANAConnection
	{
	public:
		HANAConnection(const std::wstring& dsn, const std::wstring& username, const std::wstring& password, bool autoCommit = true)
			:mDsn(dsn), mUsername(username), mPassword(password), mAutoCommit(autoCommit), mConnStatus(ConnectionStatus::Closed)
		{
			Init();
		}


		virtual ~HANAConnection()
		{
			if (0 != mConn)
			{
				SQLFreeHandle(SQL_HANDLE_DBC, mConn);
			}
		}

		operator SQLHDBC()
		{
			return mConn;
		}

		HANAPreparedStatementPtr CreatePreparedStatement()
		{
			HANAPreparedStatementPtr hsp(new HANAPreparedStatement(this, this->GetSQLHDBC()));
			return hsp;
		}

		HANAPreparedStatementPtr PrepareStatement(const std::wstring& sql)
		{
			HANAPreparedStatementPtr hsp(new HANAPreparedStatement(this, this->GetSQLHDBC()));
			hsp->Prepare(sql);
			return hsp;
		}

		HANACallableStatementPtr PrepareCall(const std::wstring& sql)
		{
			HANACallableStatementPtr hsp(new HANACallableStatement(this, this->GetSQLHDBC()));
			hsp->Prepare(sql);
			return hsp;
		}

		void SetConnectAttribute(SQLINTEGER attribute,
			SQLPOINTER value, SQLINTEGER stringLength)
		{
			SQLRETURN rc = SQLSetConnectAttr(mConn, attribute, value, stringLength);
			if (!SQL_SUCCEEDED(rc))
			{
				std::string message;
				HANAException::GetHANAErrorMessage(SQL_HANDLE_DBC, mConn, rc, message);
				throw HANAException(message.c_str());
			}
		}
		void SetAutoCommit(bool autoCommit)
		{
			SetConnectAttribute(SQL_ATTR_AUTOCOMMIT,
				autoCommit ? (SQLPOINTER)SQL_AUTOCOMMIT_ON : (SQLPOINTER)SQL_AUTOCOMMIT_OFF, SQL_IS_UINTEGER);
			mAutoCommit = autoCommit;
		}

		void Open()
		{
			SQLRETURN rc = SQLConnect(mConn, (SQLWCHAR*)mDsn.c_str(), SQL_NTS, /* DSN name */
				(SQLWCHAR*)mUsername.c_str(), SQL_NTS, /* db user id */
				(SQLWCHAR*)mPassword.c_str(), SQL_NTS /* password */
				);

			if (!SQL_SUCCEEDED(rc))
			{
				std::string message;
				HANAException::GetHANAErrorMessage(SQL_HANDLE_DBC, mConn, rc, message);
				throw HANAException(message.c_str());
			}
			mConnStatus = ConnectionStatus::Opened;
		}

		void Close()
		{
			SQLRETURN rc = SQLDisconnect(mConn);
			if (!SQL_SUCCEEDED(rc))
			{
				std::string message;
				HANAException::GetHANAErrorMessage(SQL_HANDLE_DBC, mConn, rc, message);
				throw HANAException(message.c_str());
			}
			mConnStatus = ConnectionStatus::Closed;
		}

		ConnectionStatus GetConnectionStatus()
		{
			return mConnStatus;
		}

		SQLHENV GetSQLHDBC() const
		{
			return mConn;
		}

		void Commit()
		{
			HANASQLEndTran(SQL_COMMIT);
		}

		void Rollback()
		{
			HANASQLEndTran(SQL_ROLLBACK);
		}
	private:
		HANAConnection(const HANAConnection& conn)
		{

		}

		HANAConnection& operator=(const HANAConnection& conn)
		{

		}
		void Init()
		{
			mConnStatus = ConnectionStatus::Closed;
			SQLRETURN rc = SQLAllocHandle(SQL_HANDLE_DBC, HANAEnv, &mConn);

			if (!SQL_SUCCEEDED(rc))
			{
				throw HANAException("Allocate hdbc handle failed!");
			}
			SetAutoCommit(mAutoCommit);
		}

		

		private:
			void HANASQLEndTran(int option)
			{

				SQLRETURN rc = SQLEndTran(SQL_HANDLE_DBC, mConn, option);

				std::string message;
				HANAException::GetHANAErrorMessage(SQL_HANDLE_DBC, mConn, rc, message);
				throw HANAException(message.c_str());
			}
	private:
		std::wstring mDsn;
		std::wstring mUsername;
		std::wstring mPassword;
		SQLHDBC mConn;
		bool mAutoCommit;
		ConnectionStatus mConnStatus;
	};
}