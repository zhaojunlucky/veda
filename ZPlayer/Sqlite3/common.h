#pragma once

#ifdef _WIN32
#include <Windows.h>
#endif


namespace sqlite3
{
#define SQLITE_EXPORT __declspec(dllexport)
	extern "C"
	{
#include "sqlite3.h"
	};
}