#pragma once
#include "LoggerBase.h"
#include "File.h"
namespace veda
{
	class LoggerWriter
	{
	public:
		LoggerWriter(const wchar_t* file);
		~LoggerWriter();

		void write(const wchar_t* logMessage, size_t size);
		void flush();
	private:
		WFileWriter* mWriter;
	};
}


