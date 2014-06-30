#pragma once
#include <Windows.h>
#include <sql.h>
#include <sqlext.h>
#include "HANAException.hpp"

namespace db
{
	class HANAEnvironment
	{
	public:
		HANAEnvironment(void)
		{
			InitHandle();
		}
		virtual ~HANAEnvironment(void)
		{
			ReleaseHandle();
		}
		operator SQLHENV()
		{
			return m_henv;
		}

	private:

		void InitHandle()
		{
			SQLRETURN rc = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &m_henv);
			if (!SQL_SUCCEEDED(rc))
			{
				throw HANAException("Fail to Allocate Hana Environment Handle!");
			}
#ifdef WIN32
			rc = SQLSetEnvAttr(m_henv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0);
			if (!SQL_SUCCEEDED(rc))
			{
				throw HANAException("Fail to set odbc version!");
			}
#endif
		}
		void ReleaseHandle()
		{
			if (NULL != m_henv)
			{
				SQLFreeHandle(SQL_HANDLE_ENV, m_henv);
			}
		}
	private:
		SQLHENV m_henv;
	};
}