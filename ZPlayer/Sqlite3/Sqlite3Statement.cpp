#include "Sqlite3Statement.h"

namespace sqlite3
{
	Sqlite3Statement::Sqlite3Statement(sqlite3* db)
		:mDb(db), mStmt(0)
	{
	}

	Sqlite3Statement::Sqlite3Statement(const char* sql, sqlite3* db)
		:mDb(db)
	{
		int ret = sqlite3_prepare_v2(db, sql, -1, &mStmt, 0);
		if (ret != SQLITE_OK)
		{
			throw Sqlite3Exception(sqlite3_errstr(ret), ret);
		}
	}

	Sqlite3Statement::Sqlite3Statement(const wchar_t* sql, sqlite3* db)
		:mDb(db)
	{
		int ret = sqlite3_prepare16_v2(db, sql, -1, &mStmt, 0);
		if (ret != SQLITE_OK)
		{
			throw Sqlite3Exception(sqlite3_errstr(ret), ret);
		}
	}


	Sqlite3Statement::~Sqlite3Statement()
	{
	}

	void Sqlite3Statement::executeUpdate(const char* sql)
	{
		char* errMessage = 0;
		int ret = sqlite3_exec(mDb, sql, NULL, NULL, &errMessage);
		if (SQLITE_OK != ret)
		{
			string message = errMessage;
			sqlite3_free(errMessage);

			throw Sqlite3Exception(message, ret);
		}
	}
	
	void Sqlite3Statement::executeUpdate()
	{
		int ret = sqlite3_step(mStmt);
		if (ret != SQLITE_DONE)
		{
			throw Sqlite3Exception(sqlite3_errstr(ret), ret);
		}
		sqlite3_reset(mStmt);
		sqlite3_clear_bindings(mStmt);  /* optional */
	}
	Sqlite3ResultSetPtr Sqlite3Statement::executeQuery(const char* sql)
	{
		Sqlite3ResultSetPtr ptr(new NonPrepareSqlite3ResultSet(mDb, sql));
		return ptr;
	}

	Sqlite3ResultSetPtr Sqlite3Statement::executeQuery()
	{
		Sqlite3ResultSetPtr ptr(new Sqlite3ResultSet(mDb, mStmt));
		return ptr;
	}

	void Sqlite3Statement::close()
	{
		if (NULL != mStmt)
		{
			sqlite3_finalize(mStmt);
		}
	}

	void Sqlite3Statement::bindBlob(int index, const void* value, int n, void(*xDel)(void*))
	{
		int ret = sqlite3_bind_blob(mStmt, index, value, n, xDel);
		if (SQLITE_OK != ret)
		{
			throw Sqlite3Exception(sqlite3_errstr(ret), ret);
		}
	}
	void Sqlite3Statement::bindDouble(int index, double value)
	{
		int ret = sqlite3_bind_double(mStmt, index, value);
		if (SQLITE_OK != ret)
		{
			throw Sqlite3Exception(sqlite3_errstr(ret), ret);
		}
	}
	void Sqlite3Statement::bindInteger(int index, int value)
	{
		int ret = sqlite3_bind_int(mStmt, index, value);
		if (SQLITE_OK != ret)
		{
			throw Sqlite3Exception(sqlite3_errstr(ret), ret);
		}
	}
	void Sqlite3Statement::bindInt64(int index, int64_t value)
	{
		int ret = sqlite3_bind_int64(mStmt, index, value);
		if (SQLITE_OK != ret)
		{
			throw Sqlite3Exception(sqlite3_errstr(ret), ret);
		}
	}
	void Sqlite3Statement::bindNull(int index)
	{
		int ret = sqlite3_bind_null(mStmt, index);
		if (SQLITE_OK != ret)
		{
			throw Sqlite3Exception(sqlite3_errstr(ret), ret);
		}
	}
	void Sqlite3Statement::bindText(int index, const char* value, int n, void(*xDel)(void*))
	{
		int ret = sqlite3_bind_text(mStmt, index, value,n,xDel);
		if (SQLITE_OK != ret)
		{
			throw Sqlite3Exception(sqlite3_errstr(ret), ret);
		}
	}
	void Sqlite3Statement::bindText16(int index, const void* value, int n, void(*xDel)(void*) = SQLITE_STATIC)
	{
		int ret = sqlite3_bind_text16(mStmt, index, value, n, xDel);
		if (SQLITE_OK != ret)
		{
			throw Sqlite3Exception(sqlite3_errstr(ret), ret);
		}
	}
	void Sqlite3Statement::bindValue(int index, const sqlite3_value* value)
	{
		int ret = sqlite3_bind_value(mStmt, index, value);
		if (SQLITE_OK != ret)
		{
			throw Sqlite3Exception(sqlite3_errstr(ret), ret);
		}
	}
	void Sqlite3Statement::bindZeroBlob(int index, int n)
	{
		int ret = sqlite3_bind_zeroblob(mStmt, index, n);
		if (SQLITE_OK != ret)
		{
			throw Sqlite3Exception(sqlite3_errstr(ret), ret);
		}
	}
}
