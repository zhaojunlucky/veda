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
	typedef std::shared_ptr<HANACallableStatement> HANACallableStatementPtr;
	class HANACallableStatement : public HANAStatement
	{
	public:
		void Execute()
		{
			std::string message;
			SQLRETURN rc = SQLExecute(mStmt);
			CheckParameterBind();

			if (!SQL_SUCCEEDED(rc))
			{
				HANAException::GetHANAErrorMessage(SQL_HANDLE_STMT, mStmt, rc, message);
				throw HANAException(message.c_str(), rc);
			}
		}

		HANAResultSetPtr GetResultSet()
		{
			HANAResultSetPtr hrp(new HANAResultSet(this, this->GetSQLHSTMT()));
			return hrp;
		}

		bool GetMoreResultSet()
		{
			SQLRETURN rc = SQLMoreResults(mStmt);
			bool has = SQL_SUCCEEDED(rc);
			return has;
		}

	private:
		friend class HANAConnection;
		HANACallableStatement(HANAConnection* conn, SQLHDBC sqlHdbc)
			:HANAStatement(conn, sqlHdbc)
		{
			
		}
		HANACallableStatement& operator=(HANAStatement& stmt)
		{

		}

		HANACallableStatement(HANACallableStatement& s)
			:HANAStatement(s)
		{

		}
	};
}