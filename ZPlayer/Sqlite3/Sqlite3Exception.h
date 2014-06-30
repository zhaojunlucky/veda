#pragma once
#include "common.h"
#include <exception>
#include <string>

namespace sqlite3
{
	class Sqlite3Exception : public std::exception
	{
	public:
		Sqlite3Exception(const std::string& message,int errCode);
		SQLITE_EXPORT ~Sqlite3Exception();

		SQLITE_EXPORT int getErrorCode() const;
	private:
		int mErrCode;
	};
}


