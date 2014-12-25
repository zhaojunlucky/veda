#include "stdafx.h"
#include "LoggerStream.h"

namespace veda
{

	LoggerStream::LoggerStream(const wchar_t* file, int line, Severity severity, bool writeToFile, LoggerWriter* loggerWriter)
		: mFile(file), mLine(line), mSeverity(severity), mWriteToFile(true), mLoggerWriter(loggerWriter)
	{
		SYSTEMTIME sys;

		wchar_t buf[80];

		GetLocalTime(&sys);
		swprintf_s(buf, 80, L"[%d-%02d-%02d %02d:%02d:%02d.%03d] ", sys.wYear, sys.wMonth, sys.wDay, sys.wHour, sys.wMinute, sys.wSecond, sys.wMilliseconds);
		mMessage.append(buf);
		mMessage.append(file);
		mMessage.append(L"(");
		mMessage.append(line);
		mMessage.append(L") ");
		switch (severity)
		{
		case Severity::Debug: mMessage.append(L"[D] ");  break;
		case Severity::Error:  mMessage.append(L"[E] ");  break;
		case Severity::Fatal:  mMessage.append(L"[F] ");  break;
		case Severity::Warning:  mMessage.append(L"[W] ");  break;
		default:
			mMessage.append(L"[I] "); break;
		}
	}

	LoggerStream::LoggerStream(const LoggerStream& loggerStream)
	{
		*this = loggerStream;
	}

	LoggerStream& LoggerStream::operator = (const LoggerStream& loggerStream)
	{
		this->mFile = loggerStream.mFile;
		this->mLine = loggerStream.mLine;
		this->mLoggerWriter = loggerStream.mLoggerWriter;
		this->mMessage = loggerStream.mMessage;
		this->mSeverity = loggerStream.mSeverity;
		this->mWriteToFile = loggerStream.mWriteToFile;
		return *this;
	}

	LoggerStream::~LoggerStream()
	{

	}

	LoggerStream& LoggerStream::operator << (short value)
	{
		mMessage.append(value);
		return *this;
	}
	LoggerStream& LoggerStream::operator<<(unsigned short value)
	{
		mMessage.append(value);
		return *this;
	}
	LoggerStream& LoggerStream::operator<<(int value)
	{
		mMessage.append(value);
		return *this;
	}

	LoggerStream& LoggerStream::operator<<(unsigned int value)
	{
		mMessage.append(value);
		return *this;
	}
	LoggerStream& LoggerStream::operator<<(long value)
	{
		mMessage.append(value);
		return *this;
	}
	LoggerStream& LoggerStream::operator<<(unsigned long value)
	{
		mMessage.append(value);
		return *this;
	}
	LoggerStream& LoggerStream::operator<<(long long value)
	{
		mMessage.append(value);
		return *this;
	}
	LoggerStream& LoggerStream::operator<<(unsigned long long value)
	{
		mMessage.append(value);
		return *this;
	}
	LoggerStream& LoggerStream::operator<<(float value)
	{
		mMessage.append(value);
		return *this;
	}
	LoggerStream& LoggerStream::operator<<(double value)
	{
		mMessage.append(value);
		return *this;
	}
	LoggerStream& LoggerStream::operator<<(long double value)
	{
		mMessage.append(value);
		return *this;
	}
	LoggerStream& LoggerStream::operator<<(const char *value)
	{
		WString tmp;
		tmp.from(value);
		mMessage.append(tmp.c_str(),tmp.getSize());
		return *this;
	}
	LoggerStream& LoggerStream::operator<<(const wchar_t *value)
	{
		mMessage.append(value);
		return *this;
	}
	LoggerStream& LoggerStream::operator<<(const std::string& value)
	{
		WString tmp;
		tmp.from(value.c_str(), value.size());
		mMessage.append(tmp.c_str());
		return *this;
	}
	LoggerStream& LoggerStream::operator<<(const std::wstring& value)
	{
		mMessage.append(value.c_str(),value.size());
		return *this;
	}

	LoggerStream& LoggerStream::operator<<(const AString& value)
	{
		WString tmp;
		tmp.from(value.c_str(), value.getSize());
		mMessage.append(tmp.c_str(), tmp.getSize());
		return *this;
	}
	LoggerStream& LoggerStream::operator<<(const WString& value)
	{
		mMessage.append(value.c_str());
		return *this;
	}
	LoggerStream& LoggerStream::operator<<(const AStringPtr& value)
	{
		WString tmp;
		tmp.from(value->c_str(), value->getSize());
		mMessage.append(tmp.c_str(), tmp.getSize());
		return *this;
	}
	LoggerStream& LoggerStream::operator<<(const WStringPtr& value)
	{
		mMessage.append(value->c_str());
		return *this;
	}

	LoggerStream& LoggerStream::operator<<(LoggerStream& (*manip) (LoggerStream&))
	{
		manip(*this);
		return *this;
	}

	LoggerStream& endl(LoggerStream& LoggerStream)
	{
		LoggerStream.mMessage.append(L"\n");
		if (LoggerStream.mWriteToFile && LoggerStream.mLoggerWriter)
		{
			LoggerStream.mLoggerWriter->write(LoggerStream.mMessage.c_str(), LoggerStream.mMessage.getSize());
		}
		OutputDebugStringW(LoggerStream.mMessage.c_str());
		LoggerStream.mMessage.clear();
		return LoggerStream;
	}
}
