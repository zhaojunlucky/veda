#pragma once
#include <Windows.h>
#include <assert.h>
#include <sql.h>
#include <sqlext.h>
#include <string>
#include "HANAException.hpp"
#include "HANAResultSet.hpp"
#include "Column.hpp"

namespace db
{
#define MAX_PARAMETER_SIZE 5000
	
	typedef std::shared_ptr<HANAStatement> HANAStatementPtr;

	enum ParameterType
	{
		Out = SQL_PARAM_OUTPUT,
		InOut = SQL_PARAM_INPUT_OUTPUT,
		In = SQL_PARAM_INPUT,
		Return = SQL_RETURN_VALUE
	};
	class HANAStatement
	{
	public:
		virtual ~HANAStatement()
		{
			if (NULL != mStmt)
			{
				SQLFreeHandle(SQL_HANDLE_STMT, mStmt);
			}
		}
		

		operator SQLHSTMT()
		{
			return mStmt;
		}

		SQLHSTMT GetSQLHSTMT() const
		{
			return mStmt;
		}

		void SetParameterSize(unsigned short parameterSize)
		{
			assert(parameterSize < MAX_PARAMETER_SIZE);
			std::string message;
			SQLRETURN rc = SQLSetStmtAttr(mStmt, SQL_ATTR_PARAM_STATUS_PTR, &ParamStatusArray, 0);
			if (!SQL_SUCCEEDED(rc))
			{
				HANAException::GetHANAErrorMessage(SQL_HANDLE_STMT, mStmt, rc, message);
				throw HANAException(message.c_str());
			}

			rc = SQLSetStmtAttr(mStmt, SQL_ATTR_PARAMS_PROCESSED_PTR, &ParamsProcessed, 0);

			if (!SQL_SUCCEEDED(rc))
			{	
				HANAException::GetHANAErrorMessage(SQL_HANDLE_STMT, mStmt, rc, message);
				throw HANAException(message.c_str());
			}

			rc = SQLSetStmtAttr(mStmt, SQL_ATTR_PARAM_BIND_TYPE,
				(SQLPOINTER)SQL_PARAM_BIND_BY_COLUMN, 0);

			if (!SQL_SUCCEEDED(rc))
			{
				HANAException::GetHANAErrorMessage(SQL_HANDLE_STMT, mStmt, rc, message);
				throw HANAException(message.c_str());
			}
			rc = SQLSetStmtAttr(mStmt, SQL_ATTR_PARAMSET_SIZE,
				(SQLPOINTER)parameterSize, 0);

			if (!SQL_SUCCEEDED(rc))
			{
				HANAException::GetHANAErrorMessage(SQL_HANDLE_STMT, mStmt, rc, message);
				throw HANAException(message.c_str());
			}
		}

		void Close()
		{

		}

		void BindParameter(int index, SQLSMALLINT fParamType,
			SQLSMALLINT fCType, SQLSMALLINT fSqlType, SQLULEN cbColDef,
			SQLSMALLINT ibScale, SQLPOINTER rgbValue, SQLLEN cbValueMax,
			SQLLEN *pcbValue)
		{
			assert(index > 0);
			SQLRETURN rc = 0;

			rc = SQLBindParameter(mStmt, index, fParamType, fCType, fSqlType,
				cbColDef, ibScale, rgbValue, cbValueMax, pcbValue);
			if (!SQL_SUCCEEDED(rc))
			{
				std::string message;
				HANAException::GetHANAErrorMessage(SQL_HANDLE_STMT, mStmt, rc, message);
				throw HANAException(message.c_str());
			}
		}	

		// http://msdn.microsoft.com/en-us/library/windows/desktop/ms711786(v=vs.85).aspx
		void BindColumn(unsigned short index, ParameterType parameterType, const Column& column)
		{
			const HANAColumnType hct = column.GetColumnType();
			switch (hct.sqlDataType)
			{
			case SqlDataType::SVARCHAR:
				BindParameter(index, parameterType, hct.cDataType, hct.sqlDataType, hct.size, 0, (SQLPOINTER*)column.GetDataPtr(), hct.dataSize, (SQLLEN*)column.GetDataLenPtr());
				break;
			case SqlDataType::SNVARCHAR:
				BindParameter(index, parameterType, hct.cDataType, hct.sqlDataType, hct.size, 0, (SQLPOINTER*)column.GetDataPtr(), hct.dataSize, (SQLLEN*)column.GetDataLenPtr());
				break;
			case SqlDataType::SDECIMAL:
				BindParameter(index, parameterType, hct.cDataType, hct.sqlDataType, hct.size, 0, (SQLPOINTER*)column.GetDataPtr(), hct.dataSize, (SQLLEN*)column.GetDataLenPtr());
				break;
			case SqlDataType::SINTEGER:
				BindParameter(index, parameterType, hct.cDataType, hct.sqlDataType, 10, 0, (SQLPOINTER*)column.GetDataPtr(), 0, (SQLLEN*)column.GetDataLenPtr());
				break;
			case SqlDataType::SSMALLINT:
				BindParameter(index, parameterType, hct.cDataType, hct.sqlDataType, 5, 0, (SQLPOINTER*)column.GetDataPtr(), 0, (SQLLEN*)column.GetDataLenPtr());
				break;
			case SqlDataType::STINYINT:
				BindParameter(index, parameterType, hct.cDataType, hct.sqlDataType, 3, 0, (SQLPOINTER*)column.GetDataPtr(), 0, (SQLLEN*)column.GetDataLenPtr());
				break;
			case SqlDataType::SFLOATN:
				BindParameter(index, parameterType, hct.cDataType, hct.sqlDataType, hct.size, 0, (SQLPOINTER*)column.GetDataPtr(), hct.dataSize, (SQLLEN*)column.GetDataLenPtr());
				break;
			case SqlDataType::SDOUBLE:
				BindParameter(index, parameterType, hct.cDataType, hct.sqlDataType, 15, 0, (SQLPOINTER*)column.GetDataPtr(), 0, (SQLLEN*)column.GetDataLenPtr());
				break;
			case SqlDataType::SBIGINT:
				BindParameter(index, parameterType, hct.cDataType, hct.sqlDataType, 19, 0, (SQLPOINTER*)column.GetDataPtr(), 0, (SQLLEN*)column.GetDataLenPtr());
				break;
			case SqlDataType::SDATE:
				BindParameter(index, parameterType, hct.cDataType, hct.sqlDataType, 10, 0, (SQLPOINTER*)column.GetDataPtr(), 0, (SQLLEN*)column.GetDataLenPtr());
				break;
			case SqlDataType::STIME:
				BindParameter(index, parameterType, hct.cDataType, hct.sqlDataType, 8, 0, (SQLPOINTER*)column.GetDataPtr(), 0, (SQLLEN*)column.GetDataLenPtr());
				break;
			case SqlDataType::STIMESTAMP:
				BindParameter(index, parameterType, hct.cDataType, hct.sqlDataType, 20, 0, (SQLPOINTER*)column.GetDataPtr(), 0, (SQLLEN*)column.GetDataLenPtr());
				break;
			case SqlDataType::SSECONDDATE:
				BindParameter(index, parameterType, hct.cDataType, hct.sqlDataType, 19, 0, (SQLPOINTER*)column.GetDataPtr(), 0, (SQLLEN*)column.GetDataLenPtr());
				break;
			default:throw HANAException("Unkown column type"); break;
			}
		}


	protected:
		friend class HANAConnection;
		HANAStatement(HANAConnection* conn, SQLHDBC sqlHdbc)
			:mConn(conn), mSQLHdbc(sqlHdbc), ParamsProcessed(0)
		{
			SQLRETURN rc = SQLAllocHandle(SQL_HANDLE_STMT, sqlHdbc , &mStmt);
			if (!SQL_SUCCEEDED(rc))
			{
				throw HANAException("fail to allocate statement handle");
			}
		}
		HANAStatement& operator=(HANAStatement& stmt)
		{

		}
		HANAStatement(HANAStatement&)
		{

		}

		void Prepare(const std::wstring& sql)
		{
			std::string message;
			SQLRETURN rc = SQLPrepare(mStmt, (SQLWCHAR*)sql.c_str(), SQL_NTS);
			if (!SQL_SUCCEEDED(rc))
			{
				HANAException::GetHANAErrorMessage(SQL_HANDLE_STMT, mStmt, rc, message);
				throw HANAException(message.c_str());
			}
		}

		void CheckParameterBind()
		{
			char buf[128];
			for (SQLUSMALLINT i = 0; i < ParamsProcessed; i++)
			{
				if (SQL_PARAM_ERROR == ParamStatusArray[i])
				{
					sprintf(buf,"Fail to bind %d parameter.",i+1);
					throw HANAException(buf);
				}
			}
			ParamsProcessed = 0;
		}
	protected:
		HANAConnection* mConn;
		SQLHDBC mSQLHdbc;
		SQLHSTMT mStmt;
		SQLUSMALLINT ParamsProcessed;
		SQLUSMALLINT ParamStatusArray[MAX_PARAMETER_SIZE];
	};
}