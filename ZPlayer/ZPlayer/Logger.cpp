#include "Logger.h"
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
	wchar_t buffer[1000];
	va_list argptr;
	va_start(argptr, format);
	wvsprintfW(buffer, format, argptr);
	va_end(argptr);
	OutputDebugStringW(buffer);
}
Logger::Logger()
{
}


Logger::~Logger()
{
}

Logger& Logger::operator << (const char* message)
{
	traceA("%s", message);
	return *this;
}
Logger& Logger::operator << (const wchar_t* message)
{
	traceW(L"%s", message);
	return *this;
}

Logger& Logger::log(const char* file, int line)
{
	traceA("%s(line: %d) ", file, line);
	return *this;
}
Logger& Logger::operator << (Logger& (*manip) (Logger&))
{
	manip(*this);
	return *this;
}
Logger& endl(Logger& logger)
{
	logger << "\n";
	return logger;
}
