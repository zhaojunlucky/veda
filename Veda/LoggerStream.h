#pragma once
#include "LogMessage.h"
namespace veda
{
	class VEDA_EXPORT LoggerStream
	{
		friend class Logger;
	public:
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

		LoggerStream& operator<<(LoggerStream& (*manip) (LoggerStream&));
		friend LoggerStream& endl(LoggerStream& LoggerStream);

		~LoggerStream();
	private:
		LoggerStream();
		LoggerStream(const wchar_t* file);
		
	private:

	private:
		std::multiset < long, DWORD > mLogTimeSet;
		std::hash_map<DWORD, LogMessgaePtr> mLogMessages;
		std::shared_ptr<veda::WFileWriter> mWriter;
		String mLogFile;
		bool mWriteToFile;
	};
}


