#include "Sqlite3Exception.h"

namespace sqlite3
{
	Sqlite3Exception::Sqlite3Exception(const std::string& message, int errCode)
		:std::exception(message.c_str()), mErrCode(errCode)
	{
	}


	Sqlite3Exception::~Sqlite3Exception()
	{
	}

	int Sqlite3Exception::getErrorCode() const
	{
		return mErrCode;
	}
}