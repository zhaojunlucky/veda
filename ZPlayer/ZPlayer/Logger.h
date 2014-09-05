#pragma once
#include <Windows.h>
#include <string>
#include <time.h>
#ifdef _UNICODE
#define trace traceW
#elif
#edfine trace traceA
#endif
void traceA(const char *format, ...);
void traceW(const wchar_t *format, ...);
#define LOG_INFO(logger) logger.info(__FILE__, __LINE__)
#define LOG_DEBUG(logger) logger.debug(__FILE__, __LINE__)
#define LOG_WARNING(logger) logger.warning(__FILE__, __LINE__)
#define LOG_ERROR(logger) logger.error(__FILE__, __LINE__)
#define LOG_FATAL(logger) logger.fatal(__FILE__, __LINE__)


enum Severity
{
	Debug,
	Info,
	Warning,
	Error,
	Fatal
};


class Stream
{
	friend class Logger;
public:
	Stream& operator<<(short value);
	Stream& operator<<(unsigned short value);
	Stream& operator<<(int value);
	Stream& operator<<(unsigned int value);
	Stream& operator<<(long value);
	Stream& operator<<(unsigned long value);
	Stream& operator<<(long long value);
	Stream& operator<<(unsigned long long value);
	Stream& operator<<(float value);
	Stream& operator<<(double value);
	Stream& operator<<(long double value);
	Stream& operator<<(const char *value);
	Stream& operator<<(const wchar_t *value);
	Stream& operator<<(const std::string& value);
	Stream& operator<<(const std::wstring& value);

	Stream& operator<<(Stream& (*manip) (Stream&));
	friend Stream& endl(Stream& stream);
private:
	Stream();
	~Stream();
};

class Logger
{
public:
	Logger();
	~Logger();
	Stream& log(const char* file, int line, Severity severity);
	Stream& debug(const char* file, int line);
	Stream& info(const char* file, int line);
	Stream& warning(const char* file, int line);
	Stream& error(const char* file, int line);
	Stream& fatal(const char* file, int line);
private:
	Stream* mStream;
};
