#pragma once
#include <memory>
#include <string>
#include "common.h"
#include "Sqlite3Exception.h"
#include <ZString.h>
using namespace std;
namespace sqlite3
{
	class SQLITE_EXPORT Sqlite3ResultSet
	{
	public:
		virtual ~Sqlite3ResultSet();

		// get blob, index start from 1
		virtual const void* getBlob(int colIndex);
		// get bytes, index start from 1
		virtual int getBytes(int colIndex);
		// get bytes16, index start from 1
		virtual int getBytes16(int colIndex);
		// get double, index start from 1
		virtual double getDouble(int colIndex);
		// get integer, index start from 1
		virtual int getInteger(int colIndex);
		// get int64, index start from 1
		virtual int64_t getInt64(int colIndex);
		// get unsigned char*, index start from 1
		virtual const unsigned char* getText(int colIndex);
		// get text16, index start from 1
		virtual const void* getText16(int colIndex);
		// not work for directly execute a query, index start from 1
		virtual int getColumnType(int colIndex);
		//virtual sqlite3_value getValue(int colIndex);

		// get the column count
		virtual int getColumnCount() ;
		// close the resultset
		virtual void close();
		// check does resultset has data
		bool hasNext() ;
	protected:
		friend class Sqlite3Statement;
		Sqlite3ResultSet(sqlite3* db, sqlite3_stmt* stmt);
	private:
		sqlite3* mDb;
		sqlite3_stmt* mStmt;
	};


	class NonPrepareSqlite3ResultSet : public Sqlite3ResultSet
	{
	public:
		SQLITE_EXPORT virtual ~NonPrepareSqlite3ResultSet();

		virtual const void* getBlob(int colIndex);
		virtual int getBytes(int colIndex);
		virtual int getBytes16(int colIndex);
		virtual double getDouble(int colIndex);
		virtual int getInteger(int colIndex);
		virtual int64_t getInt64(int colIndex);
		virtual const unsigned char* getText(int colIndex);
		virtual const void* getText16(int colIndex);
		// not work for directly execute a query
		virtual int getColumnType(int colIndex);
		virtual int getColumnCount() ;
		virtual void close();
		bool hasNext() ;
	private:
		friend class Sqlite3Statement;
		NonPrepareSqlite3ResultSet(sqlite3* db,const char* sql);
		const char* get(int colIndex) const;
	private:
		char** mResult;
		int mRow;
		int mCol;
		int mRowIndex;
		veda::String mTmp;
	};


	typedef shared_ptr<Sqlite3ResultSet> Sqlite3ResultSetPtr;
}
