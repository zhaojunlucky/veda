#pragma once
#include <Windows.h>
#ifdef _UNICODE
#define trace traceW
#elif
#edfine trace traceA
#endif
void traceA(const char *format, ...);
void traceW(const char *format, ...);
#define LOG_INFO(logger) logger.log(__FILE__, __LINE__)

class Logger
{
public:
	Logger();
	~Logger();

	Logger& operator << (const char* message);
	Logger& operator << (const wchar_t* message);
	Logger& operator << (Logger& (*manip) (Logger&));
	Logger& log(const char* file, int line);
	friend Logger& endl(Logger& logger);
};

