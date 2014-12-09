#pragma once
#include "common.h"
#include <string>
#include "Sqlite3Exception.h"
#include "Sqlite3Statement.h"
using namespace std;
namespace sqlite3
{
	typedef shared_ptr<Sqlite3Connection> Sqlite3ConnectionPtr;
	class SQLITE_EXPORT Sqlite3Connection
	{
	public:
		// construct a sqlite3 connection by given db path
		Sqlite3Connection(const wchar_t* db );
		// construct a sqlite3 connection by given db path
		Sqlite3Connection(const char* db);
		~Sqlite3Connection();
		// get the sqlite3 pointer
		operator sqlite3*();

		// open the database without password
		void open();
		// open the database with password
		void open(const char* key);
		// open the database with password
		void open(const wchar_t* key);
		// close the connection
		void close();
		// start a database transaction
		void beginTransaction() const;
		// commit a database transaction
		void commitTransaction() const;
		// check does sqlite3  library is  builed as thread safe
		bool isThreadSafe() const;
		// create an prepared statement with a sql
		Sqlite3StatementPtr prepare(const char* sql);
		// create an prepared statement with a sql
		Sqlite3StatementPtr prepare(const wchar_t* sql);
		// create a statement
		Sqlite3StatementPtr createStatement();
		sqlite3_int64 getLastInsertRowId();
	private:
		// disable copy contructor and = operator
		Sqlite3Connection& operator= (Sqlite3Connection&){ return *this; }
		Sqlite3Connection(Sqlite3Connection&){}
		Sqlite3Connection(){}
	private:
		sqlite3* mDb;
		string mDbFile;
	};
}


