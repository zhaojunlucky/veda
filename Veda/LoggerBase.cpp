#include "stdafx.h"
#include "LoggerBase.h"

namespace veda
{
	void traceA(const char *format, ...)
	{
		char buffer[1000];
		va_list argptr;
		va_start(argptr, format);
		wvsprintfA(buffer, format, argptr);
		va_end(argptr);
		OutputDebugStringA(buffer);
	}

	void traceW(const wchar_t *format, ...)
	{
		wchar_t buffer[2048];
		va_list argptr;
		va_start(argptr, format);
		wvsprintfW(buffer, format, argptr);
		va_end(argptr);
		OutputDebugStringW(buffer);
	}
}