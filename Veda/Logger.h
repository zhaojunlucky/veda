#pragma once
#include "LoggerStream.h"
#include "LoggerManager.h"
namespace veda
{
#ifdef _UNICODE
#define trace traceW
#define LOG_INFO LOG_INFOW
#define LOG_DEBUG LOG_DEBUGW
#define LOG_WARNING LOG_WARNINGW
#define LOG_ERROR LOG_ERRORW
#define LOG_FATAL LOG_FATALW
#elif
	#edfine trace traceA
#define LOG_INFO LOG_INFOA
#define LOG_DEBUG LOG_DEBUGA
#define LOG_WARNING LOG_WARNINGA
#define LOG_ERROR LOG_ERRORA
#define LOG_FATAL LOG_FATALA
#endif

#define LOG_INFOA(logger) logger.info(__FILE__, __LINE__)
#define LOG_DEBUGA(logger) logger.debug(__FILE__, __LINE__)
#define LOG_WARNINGA(logger) logger.warning(__FILE__, __LINE__)
#define LOG_ERRORA(logger) logger.error(__FILE__, __LINE__)
#define LOG_FATALA(logger) logger.fatal(__FILE__, __LINE__)

#define LOG_INFOW(logger) logger.info(_T(__FILE__), __LINE__)
#define LOG_DEBUGW(logger) logger.debug(_T(__FILE__), __LINE__)
#define LOG_WARNINGW(logger) logger.warning(_T(__FILE__), __LINE__)
#define LOG_ERRORW(logger) logger.error(_T(__FILE__), __LINE__)
#define LOG_FATALW(logger) logger.fatal(_T(__FILE__), __LINE__)

	class VEDA_EXPORT Logger
	{
	public:
		Logger();
		Logger(const wchar_t* logFile);
		Logger(LoggerType lt, const wchar_t* baseDir);
		~Logger();
		LoggerStream log(const char* file, int line, Severity severity);
		LoggerStream debug(const char* file, int line);
		LoggerStream info(const char* file, int line);
		LoggerStream warning(const char* file, int line);
		LoggerStream error(const char* file, int line);
		LoggerStream fatal(const char* file, int line);

		LoggerStream log(const wchar_t* file, int line, Severity severity);
		LoggerStream debug(const wchar_t* file, int line);
		LoggerStream info(const wchar_t* file, int line);
		LoggerStream warning(const wchar_t* file, int line);
		LoggerStream error(const wchar_t* file, int line);
		LoggerStream fatal(const wchar_t* file, int line);
	private:
		StringPtr generateFileName(LoggerType lt, const wchar_t* baseDir);
	private:
		LoggerWriter* mLoggerWriter;
	};
}

