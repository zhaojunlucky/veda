#include "Sqlite3ResultSet.h"


namespace sqlite3
{
	Sqlite3ResultSet::Sqlite3ResultSet(sqlite3* db, sqlite3_stmt* stmt)
		:mDb(db), mStmt(stmt)
	{

	}


	Sqlite3ResultSet::~Sqlite3ResultSet()
	{
	}

	const void* Sqlite3ResultSet::getBlob(int colIndex)
	{
		return sqlite3_column_blob(mStmt, colIndex - 1);
	}
	int Sqlite3ResultSet::getBytes(int colIndex)
	{
		return sqlite3_column_bytes(mStmt, colIndex - 1);
	}
	int Sqlite3ResultSet::getBytes16(int colIndex)
	{
		return sqlite3_column_bytes16(mStmt, colIndex - 1);
	}

	double Sqlite3ResultSet::getDouble(int colIndex)
	{
		return sqlite3_column_double(mStmt, colIndex - 1);
	}
	int Sqlite3ResultSet::getInteger(int colIndex)
	{
		return sqlite3_column_int(mStmt, colIndex - 1);
	}
	int64_t Sqlite3ResultSet::getInt64(int colIndex)
	{
		return sqlite3_column_int64(mStmt, colIndex - 1);
	}
	const unsigned char* Sqlite3ResultSet::getText(int colIndex)
	{
		return sqlite3_column_text(mStmt, colIndex - 1);
	}
	const void* Sqlite3ResultSet::getText16(int colIndex)
	{
		return sqlite3_column_text16(mStmt, colIndex - 1);
	}
	int Sqlite3ResultSet::getColumnType(int colIndex)
	{
		return sqlite3_column_type(mStmt, colIndex - 1);
	}
	int Sqlite3ResultSet::getColumnCount()
	{
		return sqlite3_column_count(mStmt);
	}
	void Sqlite3ResultSet::close()
	{
		sqlite3_reset(mStmt);
		sqlite3_clear_bindings(mStmt);  /* optional */
	}

	bool Sqlite3ResultSet::hasNext()
	{
		return sqlite3_step(mStmt) == SQLITE_ROW;
	}


	/*
	 * class NonPrepareSqlite3ResultSet implementation
	 */

	NonPrepareSqlite3ResultSet::NonPrepareSqlite3ResultSet(sqlite3* db, const char* sql)
		:Sqlite3ResultSet(0, 0)
	{
		mRow = 0;
		mCol = 0;
		mRowIndex = 1;
		char* errMessage = 0;
		int ret = sqlite3_get_table(db, sql, &mResult, &mRow, &mCol, &errMessage);
		if (SQLITE_OK != ret)
		{
			string message = errMessage;
			sqlite3_free(errMessage);

			throw Sqlite3Exception(message, ret);
		}

	}

	NonPrepareSqlite3ResultSet::~NonPrepareSqlite3ResultSet()
	{

	}

	const void* NonPrepareSqlite3ResultSet::getBlob(int colIndex)
	{
		return get(colIndex);
	}
	int NonPrepareSqlite3ResultSet::getBytes(int colIndex)
	{
		return strlen(get(colIndex));
	}
	int NonPrepareSqlite3ResultSet::getBytes16(int colIndex)
	{
		const char* data = get(colIndex);
		veda::WString tmp;
		tmp.from(data);
		
		return tmp.getSize();
	}
	double NonPrepareSqlite3ResultSet::getDouble(int colIndex)
	{
		return atof(get(colIndex));
	}
	int NonPrepareSqlite3ResultSet::getInteger(int colIndex)
	{
		return atoi(get(colIndex));
	}
	int64_t NonPrepareSqlite3ResultSet::getInt64(int colIndex)
	{
		return atoll(get(colIndex));
	}
	const unsigned char* NonPrepareSqlite3ResultSet::getText(int colIndex)
	{
		return (const unsigned char*)get(colIndex);
	}
	const void* NonPrepareSqlite3ResultSet::getText16(int colIndex)
	{
		const char* data = get(colIndex);
		mTmp.from(data);
		return mTmp.c_str();
	}
	int NonPrepareSqlite3ResultSet::getColumnType(int colIndex)
	{
		return 0;
	}
	int NonPrepareSqlite3ResultSet::getColumnCount()
	{
		return mCol;
	}
	void NonPrepareSqlite3ResultSet::close()
	{
		sqlite3_free_table(mResult);
	}
	bool NonPrepareSqlite3ResultSet::hasNext()
	{
		return mRowIndex < mRow;
	}

	const char* NonPrepareSqlite3ResultSet::get(int colIndex) const
	{
		return mResult[mRow*mCol + colIndex - 1];
	}
}