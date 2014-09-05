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

Stream::Stream()
{

}
Stream::~Stream()
{

}
Stream& Stream::operator << (short value)
{
	traceA("%d", value);
	return *this;
}
Stream& Stream::operator<<(unsigned short value)
{
	traceA("%u", value);
	return *this;
}
Stream& Stream::operator<<(int value)
{
	traceA("%d", value);
	return *this;
}

Stream& Stream::operator<<(unsigned int value)
{
	traceA("%u", value);
	return *this;
}
Stream& Stream::operator<<(long value)
{
	traceA("%ld", value);
	return *this;
}
Stream& Stream::operator<<(unsigned long value)
{
	traceA("%ud", value);
	return *this;
}
Stream& Stream::operator<<(long long value)
{
	traceA("%ld", value);
	return *this;
}
Stream& Stream::operator<<(unsigned long long value)
{
	traceA("%uld", value);
	return *this;
}
Stream& Stream::operator<<(float value)
{
	traceA("%f", value);
	return *this;
}
Stream& Stream::operator<<(double value)
{
	traceA("%f", value);
	return *this;
}
Stream& Stream::operator<<(long double value)
{
	traceA("%lf", value);
	return *this;
}
Stream& Stream::operator<<(const char *value)
{
	traceA("%s", value);
	return *this;
}
Stream& Stream::operator<<(const wchar_t *value)
{
	traceW(L"%s", value);
	return *this;
}
Stream& Stream::operator<<(const std::string& value)
{
	traceA("%s", value.c_str());
	return *this;
}
Stream& Stream::operator<<(const std::wstring& value)
{
	traceW(L"%s", value.c_str());
	return *this;
}

Stream& Stream::operator<<(Stream& (*manip) (Stream&))
{
	manip(*this);
	return *this;
}

Stream& endl(Stream& stream)
{
	traceA("%s", "\n");
	return stream;
}


Logger::Logger()
{
	mStream = new Stream();
}


Logger::~Logger()
{
	if (mStream)
	{
		delete mStream;
	}
}

Stream& Logger::log(const char* file, int line, Severity severity)
{
	/*time_t nowtime;
	nowtime = time(NULL);
	struct tm *local;
	local = localtime(&nowtime);*/
	SYSTEMTIME sys;

	char buf[80];
	//strftime(buf, 80, "%Y-%m-%d %H:%M:%S.%z", local);

	GetLocalTime(&sys);
	sprintf(buf,"%d-%02d-%02d %02d:%02d:%02d.%03d", sys.wYear, sys.wMonth, sys.wDay, sys.wHour, sys.wMinute, sys.wSecond, sys.wMilliseconds);
	switch (severity)
	{
	case Severity::Debug:traceA("[%s] %s(%d) [D] ", buf, file, line); break;
	case Severity::Error:traceA("[%s] %s(%d) [E] ", buf, file, line); break;
	case Severity::Fatal:traceA("[%s] %s(%d) [F] ", buf, file, line); break;
	case Severity::Warning:traceA("[%s] %s(%d) [W] ", buf, file, line); break;
	default:
		traceA("[%s] %s(%d) [I] ", buf, file, line); break;
	}
	return *mStream;
}


Stream& Logger::debug(const char* file, int line)
{
	return log(file, line, Severity::Debug);
}
Stream& Logger::info(const char* file, int line)
{
	return log(file, line, Severity::Info);
}
Stream& Logger::warning(const char* file, int line)
{
	return log(file, line, Severity::Warning);
}
Stream& Logger::error(const char* file, int line)
{
	return log(file, line, Severity::Error);
}
Stream& Logger::fatal(const char* file, int line)
{
	return log(file, line, Severity::Fatal);
}

