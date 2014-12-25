#include "stdafx.h"
#include "LoggerManager.h"

namespace veda
{
	LoggerManager::LoggerManager()
	{
	}


	LoggerManager::~LoggerManager()
	{
		for (auto it = mWritterMap.begin(); it != mWritterMap.end(); ++it)
		{
			delete it->second;
		}
	}

	LoggerWriter* LoggerManager::findOrCreateLoggerWriter(const wchar_t* file)
	{
		std::wstring writerName = file;
		LoggerWriter* writer = NULL;
		mMutex.lock();
		auto it = mWritterMap.find(writerName);
		if (it == mWritterMap.end())
		{
			writer = new LoggerWriter(file);
		}
		else
		{
			writer = it->second;
		}
		mMutex.unlock();
		return writer;
	}
}