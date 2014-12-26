#include "stdafx.h"
#include "Logger.h"
#include "Datetime.h"
#include "PathUtil.h"

namespace veda
{
	Logger::Logger()
	{
		mLoggerWriter = NULL;
	}
	Logger::Logger(const wchar_t* logFile)
	{
		mLoggerWriter = LoggerManager::getInstance()->findOrCreateLoggerWriter(logFile);
	}
	Logger::Logger(LoggerType lt, const wchar_t* baseDir)
	{
		auto path = generateFileName(lt, baseDir);
		mLoggerWriter = LoggerManager::getInstance()->findOrCreateLoggerWriter(path->c_str());
	}
	Logger::~Logger()
	{
		
	}

	LoggerStream Logger::log(const char* file, int line, Severity severity)
	{
		/*time_t nowtime;
		nowtime = time(NULL);
		struct tm *local;
		local = localtime(&nowtime);*/
		//SYSTEMTIME sys;

		//char buf[80];
		////strftime(buf, 80, "%Y-%m-%d %H:%M:%S.%z", local);

		//GetLocalTime(&sys);
		//sprintf_s(buf, 80, "%d-%02d-%02d %02d:%02d:%02d.%03d", sys.wYear, sys.wMonth, sys.wDay, sys.wHour, sys.wMinute, sys.wSecond, sys.wMilliseconds);
		//switch (severity)
		//{
		//case Severity::Debug:traceA("[%s] %s(%d) [D] ", buf, file, line); break;
		//case Severity::Error:traceA("[%s] %s(%d) [E] ", buf, file, line); break;
		//case Severity::Fatal:traceA("[%s] %s(%d) [F] ", buf, file, line); break;
		//case Severity::Warning:traceA("[%s] %s(%d) [W] ", buf, file, line); break;
		//default:
		//	traceA("[%s] %s(%d) [I] ", buf, file, line); break;
		//}
		WString tmp;
		tmp.from(file);
		return std::move(LoggerStream(tmp.c_str(), line, severity, true, mLoggerWriter));
	}


	LoggerStream Logger::debug(const char* file, int line)
	{
		return std::move(log(file, line, Severity::Debug));
	}
	LoggerStream Logger::info(const char* file, int line)
	{
		return std::move(log(file, line, Severity::Info));
	}
	LoggerStream Logger::warning(const char* file, int line)
	{
		return std::move(log(file, line, Severity::Warning));
	}
	LoggerStream Logger::error(const char* file, int line)
	{
		return std::move(log(file, line, Severity::Error));
	}
	LoggerStream Logger::fatal(const char* file, int line)
	{
		return std::move(log(file, line, Severity::Fatal));
	}

	LoggerStream Logger::log(const wchar_t* file, int line, Severity severity)
	{
		/*time_t nowtime;
		nowtime = time(NULL);
		struct tm *local;
		local = localtime(&nowtime);*/
		//SYSTEMTIME sys;

		//wchar_t buf[80];
		////strftime(buf, 80, "%Y-%m-%d %H:%M:%S.%z", local);

		//GetLocalTime(&sys);
		//swprintf_s(buf, 80, L"%d-%02d-%02d %02d:%02d:%02d.%03d", sys.wYear, sys.wMonth, sys.wDay, sys.wHour, sys.wMinute, sys.wSecond, sys.wMilliseconds);

		//switch (severity)
		//{
		//case Severity::Debug:traceW(L"[%s] %s(%d) [D] ", buf, file, line); break;
		//case Severity::Error:traceW(L"[%s] %s(%d) [E] ", buf, file, line); break;
		//case Severity::Fatal:traceW(L"[%s] %s(%d) [F] ", buf, file, line); break;
		//case Severity::Warning:traceW(L"[%s] %s(%d) [W] ", buf, file, line); break;
		//default:
		//	traceW(L"[%s] %s(%d) [I] ", buf, file, line); break;
		//}
		return std::move(LoggerStream(file, line, severity, true, mLoggerWriter));
	}


	LoggerStream Logger::debug(const wchar_t* file, int line)
	{
		return std::move(log(file, line, Severity::Debug));
	}
	LoggerStream Logger::info(const wchar_t* file, int line)
	{
		return std::move(log(file, line, Severity::Info));
	}
	LoggerStream Logger::warning(const wchar_t* file, int line)
	{
		return std::move(log(file, line, Severity::Warning));
	}
	LoggerStream Logger::error(const wchar_t* file, int line)
	{
		return std::move(log(file, line, Severity::Error));
	}
	LoggerStream Logger::fatal(const wchar_t* file, int line)
	{
		return std::move(log(file, line, Severity::Fatal));
	}

	StringPtr Logger::generateFileName(LoggerType lt, const wchar_t* baseDir)
	{
		String pDir = (NULL == baseDir) ? L"" : baseDir;
		Datetime now;
		wchar_t buf[1024];
		if (lt == LoggerType::Daily)
		{
			static wchar_t* daily = L"%04d-%02d-%02d";
			swprintf_s(buf, 1024, daily, now.getYear(), now.getMonth(), now.getDay());
		}
		else if (lt == LoggerType::Monthly)
		{
			static wchar_t* monthly = L"%04d-%02d";
			swprintf_s(buf, 1024, monthly, now.getYear(), now.getMonth());
		}
		else if (lt == LoggerType::Timely)
		{
			static wchar_t* timely = L"%04d-%02d-%02d %02d_%02d_%02d_%03d";
			swprintf_s(buf, 1024, timely, now.getYear(), now.getMonth(), now.getDay(), now.getHour(), now.getMinute(), now.getSecond(), now.getMillisecond());
		}
		else if (lt == LoggerType::Weekly)
		{
			static wchar_t* weekly = L"%04d_%02d";
			swprintf_s(buf, 1024, weekly, now.getYear(), now.getWeekOfYear());
		}
		if (pDir.getSize() > 0)
		{
			PathUtil p;
			return p.combinePath(pDir.getData(), buf, 0);
		}
		return makeStringPtr(buf);
	}
}
