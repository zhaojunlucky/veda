#pragma once
#include <exception>
#include <string>
#include <sql.h>
#include <sqlext.h>

namespace db
{
	class HANAException :
		public std::exception
	{
	public:
		HANAException(const char* error, int code)
			:exception(error), m_errorCode(code)
		{

		}
		HANAException(const char* error)
			:exception(error), m_errorCode(0)
		{

		}
		virtual ~HANAException(void)
		{

		}
		int GetErrorCode()
		{
			return m_errorCode;
		}
	private:
		friend class HANAConnection;
		friend class HANAStatement;
		friend class HANAResultSet;
		friend class HANAPreparedStatement;
		friend class HANACallableStatement;
		static void GetHANAErrorMessage(SQLSMALLINT hand_type, SQLHANDLE handle, SQLRETURN r,
			std::string & errorMessage)
		{
			errorMessage.clear();
			SQLCHAR Error[1024 * 10];
			SQLCHAR State[10];
			SQLSMALLINT ErrLen = 0;
			SQLSMALLINT i = 1;
			SQLINTEGER NativeErr;

			SQLRETURN rc;
			do
			{
				rc = SQLGetDiagRecA(hand_type, handle, i, State, &NativeErr, Error,
					sizeof(Error), &ErrLen);
				if (rc == SQL_NO_DATA)
					break;
				Error[ErrLen] = '\0';
				errorMessage += (char*)Error;
				i++;
			} while (rc == SQL_SUCCESS);
		}
	private:
		int m_errorCode;
	};
}