#pragma once
#include "LoggerBase.h"
#include <memory>
namespace veda
{
	class VEDA_EXPORT LogMessage
	{
	public:
		LogMessage(DWORD threadId, const wchar_t* log);
		virtual ~LogMessage();

		DWORD getThreadId();

		veda::String& getLogMessage();
	private:
		DWORD mThreadId;
		veda::String mLog;
	};
	typedef std::shared_ptr<LogMessage> LogMessgaePtr;
}

