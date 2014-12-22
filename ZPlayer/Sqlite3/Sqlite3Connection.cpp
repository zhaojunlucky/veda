#include "Sqlite3Connection.h"
#include <ZString.h>

namespace sqlite3
{
	Sqlite3Connection::Sqlite3Connection(const wchar_t* db)
		:mDb(0)
	{
		mDbFile = db;
	}

	Sqlite3Connection::Sqlite3Connection(const char* db)
		: mDb(0)
	{
		if (NULL != db)
		{
			mDbFile.from(db);
		}
	}


	Sqlite3Connection::~Sqlite3Connection()
	{

	}

	Sqlite3Connection::operator sqlite3*()
	{
		return mDb;
	}
	void Sqlite3Connection::open()
	{
		int ret = sqlite3_open16(mDbFile.c_str(), &mDb);
		if (ret != SQLITE_OK)
		{
			throw Sqlite3Exception(sqlite3_errstr(ret), ret);
		}
	}

	void Sqlite3Connection::open(const char* key)
	{
		open();
		int ret = sqlite3_key(mDb, key, strlen(key));
		if (ret != SQLITE_OK)
		{
			throw Sqlite3Exception(sqlite3_errstr(ret), ret);
		}
	}
	void Sqlite3Connection::open(const wchar_t* key)
	{
		veda::AString tmp;
		tmp.from(key);
		open(tmp.c_str());
	}

	void Sqlite3Connection::beginTransaction() const
	{
		char* errMessage;
		int ret = sqlite3_exec(mDb, "BEGIN TRANSACTION", NULL, NULL,&errMessage);
		if (SQLITE_OK != ret)
		{
			string message = errMessage;
			sqlite3_free(errMessage);

			throw Sqlite3Exception(message, ret);
		}
	}
	void Sqlite3Connection::commitTransaction() const
	{
		char* errMessage;
		int ret = sqlite3_exec(mDb, "COMMIT TRANSACTION", NULL, NULL, &errMessage);
		if (SQLITE_OK != ret)
		{
			string message = errMessage;
			sqlite3_free(errMessage);

			throw Sqlite3Exception(message, ret);
		}
	}
	
	void Sqlite3Connection::close()
	{
		if (NULL != mDb)
		{
			sqlite3_close(mDb);
		}
	}

	bool Sqlite3Connection::isThreadSafe() const
	{
		return SQLITE_OK == sqlite3_threadsafe();
	}

	Sqlite3StatementPtr Sqlite3Connection::prepare(const char* sql)
	{
		Sqlite3StatementPtr ptr(new Sqlite3Statement(sql,mDb));
		return ptr;
	}

	Sqlite3StatementPtr Sqlite3Connection::prepare(const wchar_t* sql)
	{
		Sqlite3StatementPtr ptr(new Sqlite3Statement(sql, mDb));
		return ptr;
	}
	Sqlite3StatementPtr Sqlite3Connection::createStatement()
	{
		Sqlite3StatementPtr ptr(new Sqlite3Statement(mDb));
		return ptr;
	}

	sqlite3_int64 Sqlite3Connection::getLastInsertRowId()
	{
		return sqlite3_last_insert_rowid(mDb);
	}
}
