#include "stdafx.h"
#include "Logger.h"
#include "Datetime.h"

namespace veda
{
	Logger::Logger()
	{
		mStream = new LoggerStream();
	}
	Logger::Logger(const wchar_t* logFile)
	{
		mStream = new LoggerStream(logFile);
	}

	Logger::~Logger()
	{
		if (mStream)
		{
			delete mStream;
		}
	}

	LoggerStream& Logger::log(const char* file, int line, Severity severity)
	{
		/*time_t nowtime;
		nowtime = time(NULL);
		struct tm *local;
		local = localtime(&nowtime);*/
		SYSTEMTIME sys;

		char buf[80];
		//strftime(buf, 80, "%Y-%m-%d %H:%M:%S.%z", local);

		GetLocalTime(&sys);
		sprintf_s(buf, 80, "%d-%02d-%02d %02d:%02d:%02d.%03d", sys.wYear, sys.wMonth, sys.wDay, sys.wHour, sys.wMinute, sys.wSecond, sys.wMilliseconds);
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


	LoggerStream& Logger::debug(const char* file, int line)
	{
		return log(file, line, Severity::Debug);
	}
	LoggerStream& Logger::info(const char* file, int line)
	{
		return log(file, line, Severity::Info);
	}
	LoggerStream& Logger::warning(const char* file, int line)
	{
		return log(file, line, Severity::Warning);
	}
	LoggerStream& Logger::error(const char* file, int line)
	{
		return log(file, line, Severity::Error);
	}
	LoggerStream& Logger::fatal(const char* file, int line)
	{
		return log(file, line, Severity::Fatal);
	}

	LoggerStream& Logger::log(const wchar_t* file, int line, Severity severity)
	{
		/*time_t nowtime;
		nowtime = time(NULL);
		struct tm *local;
		local = localtime(&nowtime);*/
		SYSTEMTIME sys;

		wchar_t buf[80];
		//strftime(buf, 80, "%Y-%m-%d %H:%M:%S.%z", local);

		GetLocalTime(&sys);
		swprintf_s(buf, 80, L"%d-%02d-%02d %02d:%02d:%02d.%03d", sys.wYear, sys.wMonth, sys.wDay, sys.wHour, sys.wMinute, sys.wSecond, sys.wMilliseconds);
	
		switch (severity)
		{
		case Severity::Debug:traceW(L"[%s] %s(%d) [D] ", buf, file, line); break;
		case Severity::Error:traceW(L"[%s] %s(%d) [E] ", buf, file, line); break;
		case Severity::Fatal:traceW(L"[%s] %s(%d) [F] ", buf, file, line); break;
		case Severity::Warning:traceW(L"[%s] %s(%d) [W] ", buf, file, line); break;
		default:
			traceW(L"[%s] %s(%d) [I] ", buf, file, line); break;
		}
		return *mStream;
	}


	LoggerStream& Logger::debug(const wchar_t* file, int line)
	{
		return log(file, line, Severity::Debug);
	}
	LoggerStream& Logger::info(const wchar_t* file, int line)
	{
		return log(file, line, Severity::Info);
	}
	LoggerStream& Logger::warning(const wchar_t* file, int line)
	{
		return log(file, line, Severity::Warning);
	}
	LoggerStream& Logger::error(const wchar_t* file, int line)
	{
		return log(file, line, Severity::Error);
	}
	LoggerStream& Logger::fatal(const wchar_t* file, int line)
	{
		return log(file, line, Severity::Fatal);
	}
}
