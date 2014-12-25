#pragma once
#include "LoggerBase.h"
#include "LoggerWriter.h"
namespace veda
{
	class VEDA_EXPORT LoggerStream
	{
		friend class Logger;
	public:

		LoggerStream(const LoggerStream& loggerStream);
		LoggerStream& operator=(const LoggerStream& loggerStream);
		LoggerStream& operator<<(short value);
		LoggerStream& operator<<(unsigned short value);
		LoggerStream& operator<<(int value);
		LoggerStream& operator<<(unsigned int value);
		LoggerStream& operator<<(long value);
		LoggerStream& operator<<(unsigned long value);
		LoggerStream& operator<<(long long value);
		LoggerStream& operator<<(unsigned long long value);
		LoggerStream& operator<<(float value);
		LoggerStream& operator<<(double value);
		LoggerStream& operator<<(long double value);
		LoggerStream& operator<<(const char *value);
		LoggerStream& operator<<(const wchar_t *value);
		LoggerStream& operator<<(const std::string& value);
		LoggerStream& operator<<(const std::wstring& value);
		LoggerStream& operator<<(const AString& value);
		LoggerStream& operator<<(const WString& value);
		LoggerStream& operator<<(const AStringPtr& value);
		LoggerStream& operator<<(const WStringPtr& value);

		LoggerStream& operator<<(LoggerStream& (*manip) (LoggerStream&));
		friend LoggerStream& endl(LoggerStream& LoggerStream);

		~LoggerStream();
	private:

		LoggerStream(const wchar_t* file, int line, Severity severity, bool writeToFile, LoggerWriter* loggerWriter);

	private:
		String mFile;
		int mLine;
		Severity mSeverity;
		bool mWriteToFile;
		LoggerWriter* mLoggerWriter;
		String mMessage;
	};
}


