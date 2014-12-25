#include "stdafx.h"
#include "LoggerWriter.h"

namespace veda
{
	LoggerWriter::LoggerWriter(const wchar_t* file)
	{
		mWriter = new WFileWriter(file, FileEncoding::UTF8);
	}


	LoggerWriter::~LoggerWriter()
	{
		if (mWriter)
		{
			mWriter->close();
			delete mWriter;
		}
	}

	void LoggerWriter::write(const wchar_t* logMessage,size_t size)
	{
		mWriter->Write(logMessage,size);
	}
	void LoggerWriter::flush()
	{
		
	}
}