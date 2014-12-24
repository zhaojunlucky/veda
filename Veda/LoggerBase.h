#pragma once
#include <Windows.h>
#include <tchar.h>
#include <time.h>
#include <memory>
#include <hash_map>
#include <set>
#include "ZString.h"
#include "File.h"
#include "veda.h"
namespace veda
{
#ifdef _UNICODE
#define trace traceW
#define LOG_FATAL LOG_FATALW
#elif
#edfine trace traceA
#endif

	enum Severity
	{
		Debug,
		Info,
		Warning,
		Error,
		Fatal
	};

	void traceA(const char *format, ...);
	void traceW(const wchar_t *format, ...);

}


