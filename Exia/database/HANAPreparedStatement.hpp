#pragma once
#include <Windows.h>
#include <assert.h>
#include <sql.h>
#include <sqlext.h>
#include <string>
#include "HANAStatement.hpp"
#include <memory>


namespace db
{
	typedef std::shared_ptr<HANAPreparedStatement> HANAPreparedStatementPtr;
	class HANAPreparedStatement: public HANAStatement
	{
	public:
		virtual ~HANAPreparedStatement()
		{

		}

		int ExecuteUpdate()
		{
			std::string message;
			SQLRETURN rc = SQLExecute(mStmt);
			CheckParameterBind();

			if (!SQL_SUCCEEDED(rc))
			{
				HANAException::GetHANAErrorMessage(SQL_HANDLE_STMT, mStmt, rc, message);
				throw HANAException(message.c_str(), rc);
			}
			return 0;
		}
		int ExecuteUpdate(const std::wstring& sql)
		{
			std::string message;
			SQLRETURN rc = SQLExecDirect(mStmt, (SQLWCHAR*)sql.c_str(), SQL_NTS);

			if (!SQL_SUCCEEDED(rc))
			{
				HANAException::GetHANAErrorMessage(SQL_HANDLE_STMT, mStmt, rc, message);
				throw HANAException(message.c_str());
			}
			return 0;
		}
		HANAResultSetPtr ExecuteQuery()
		{
			std::string message;
			SQLRETURN rc = SQLExecute(mStmt);
			CheckParameterBind();

			if (!SQL_SUCCEEDED(rc))
			{
				HANAException::GetHANAErrorMessage(SQL_HANDLE_STMT, mStmt, rc, message);
				throw HANAException(message.c_str());
			}
			HANAResultSetPtr hrp(new HANAResultSet(this, this->GetSQLHSTMT()));
			return hrp;
		}
		HANAResultSetPtr ExecuteQuery(const std::wstring& sql)
		{
			std::string message;
			SQLRETURN rc = SQLExecDirect(mStmt, (SQLWCHAR*)sql.c_str(), SQL_NTS);

			if (!SQL_SUCCEEDED(rc))
			{
				HANAException::GetHANAErrorMessage(SQL_HANDLE_STMT, mStmt, rc, message);
				throw HANAException(message.c_str());
			}
			HANAResultSetPtr hrp(new HANAResultSet(this, this->GetSQLHSTMT()));
			return hrp;
		}

	private:
		friend class HANAConnection;
		HANAPreparedStatement(HANAConnection* conn, SQLHDBC sqlHdbc)
			:HANAStatement(conn,sqlHdbc)
		{

		}
		HANAPreparedStatement& operator=(HANAStatement& stmt)
		{

		}

		HANAPreparedStatement(HANAPreparedStatement& s)
			:HANAStatement(s)
		{

		}
	};
}