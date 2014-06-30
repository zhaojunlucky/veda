#pragma once
#include <memory>
#include "common.h"
#include "Sqlite3ResultSet.h"
#include "Sqlite3Exception.h"
using namespace std;

namespace sqlite3
{
	typedef shared_ptr<Sqlite3Statement> Sqlite3StatementPtr;

	class SQLITE_EXPORT Sqlite3Statement
	{
	public:
		~Sqlite3Statement();
		// execute a sql
		void executeUpdate(const char* sql);
		// call this function each time when binding parameter finished
		// it's not the same as big db operation concept
		void executeUpdate();
		Sqlite3ResultSetPtr executeQuery(const char* sql);
		// call this function each time when binding parameter finished
		// it's not the same as big db operation concept
		Sqlite3ResultSetPtr executeQuery();
		// close the statement
		void close();
		// bind blob parametrer, index start with 0
		void bindBlob(int index, const void* value, int n, void(*)(void*));
		// bind double parametrer, index start with 0
		void bindDouble(int index, double value);
		// bind int parametrer, index start with 0
		void bindInteger(int index, int value);
		// bind int64 parametrer, index start with 0
		void bindInt64(int index, int64_t value);
		// bind null parametrer, index start with 0
		void bindNull(int index);
		// bind text parametrer, index start with 0
		void bindText(int index, const char* value, int n, void(*)(void*));
		// bind text16 parametrer, index start with 0
		void bindText16(int index, const void* value, int n, void(*)(void*));
		// bind value parametrer, index start with 0
		void bindValue(int index, const sqlite3_value* value);
		// bind zeroblob parametrer, index start with 0
		void bindZeroBlob(int index, int n);
	private:
		Sqlite3Statement(sqlite3* db);
		Sqlite3Statement(const char* sql, sqlite3* db);
		Sqlite3Statement(Sqlite3Statement&){};
		Sqlite3Statement& operator=(Sqlite3Statement&){ return *this; };
	private:
		friend class Sqlite3Connection;
		sqlite3_stmt* mStmt;
		sqlite3* mDb;
	};
}


