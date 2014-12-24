#include "stdafx.h"
#include "LoggerStream.h"

namespace veda
{
	LoggerStream::LoggerStream()
		:mWriteToFile(false)
	{
	}

	LoggerStream::LoggerStream(const wchar_t* file)
		: mLogFile(file), mWriteToFile(true)
	{
		 
	}
	LoggerStream::~LoggerStream()
	{

	}

	LoggerStream& LoggerStream::operator << (short value)
	{
		traceA("%d", value);
		return *this;
	}
	LoggerStream& LoggerStream::operator<<(unsigned short value)
	{
		traceA("%u", value);
		return *this;
	}
	LoggerStream& LoggerStream::operator<<(int value)
	{
		traceA("%d", value);
		return *this;
	}

	LoggerStream& LoggerStream::operator<<(unsigned int value)
	{
		traceA("%u", value);
		return *this;
	}
	LoggerStream& LoggerStream::operator<<(long value)
	{
		traceA("%ld", value);
		return *this;
	}
	LoggerStream& LoggerStream::operator<<(unsigned long value)
	{
		traceA("%ud", value);
		return *this;
	}
	LoggerStream& LoggerStream::operator<<(long long value)
	{
		traceA("%ld", value);
		return *this;
	}
	LoggerStream& LoggerStream::operator<<(unsigned long long value)
	{
		traceA("%uld", value);
		return *this;
	}
	LoggerStream& LoggerStream::operator<<(float value)
	{
		traceA("%f", value);
		return *this;
	}
	LoggerStream& LoggerStream::operator<<(double value)
	{
		traceA("%f", value);
		return *this;
	}
	LoggerStream& LoggerStream::operator<<(long double value)
	{
		traceA("%lf", value);
		return *this;
	}
	LoggerStream& LoggerStream::operator<<(const char *value)
	{
		traceA("%s", value);
		return *this;
	}
	LoggerStream& LoggerStream::operator<<(const wchar_t *value)
	{
		traceW(L"%s", value);
		return *this;
	}
	LoggerStream& LoggerStream::operator<<(const std::string& value)
	{
		traceA("%s", value.c_str());
		return *this;
	}
	LoggerStream& LoggerStream::operator<<(const std::wstring& value)
	{
		traceW(L"%s", value.c_str());
		return *this;
	}

	LoggerStream& LoggerStream::operator<<(LoggerStream& (*manip) (LoggerStream&))
	{
		manip(*this);
		return *this;
	}

	LoggerStream& endl(LoggerStream& LoggerStream)
	{
		traceA("%s", "\n");
		return LoggerStream;
	}
}
