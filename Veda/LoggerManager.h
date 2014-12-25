#pragma once
#include <string>
#include <hash_map>
#include <mutex>

#include "LoggerWriter.h"
#include "veda.h"

namespace veda
{
	class LoggerManager
	{
	public:
		LoggerManager();
		~LoggerManager();

		static LoggerManager* getInstance()
		{
			static LoggerManager instance;
			return &instance;
		}

		LoggerWriter* findOrCreateLoggerWriter(const wchar_t* file);
	private:
		std::hash_map<std::wstring, LoggerWriter*> mWritterMap;
		std::mutex mMutex;
	};
}


