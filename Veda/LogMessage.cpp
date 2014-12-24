#include "stdafx.h"
#include "LogMessage.h"

namespace veda
{
	LogMessage::LogMessage(DWORD threadId, const wchar_t* log)
		:mThreadId(threadId), mLog(log)
	{

	}


	LogMessage::~LogMessage()
	{
	}

	DWORD LogMessage::getThreadId()
	{
		return mThreadId;
	}

	veda::String& LogMessage::getLogMessage()
	{
		return mLog;
	}
}

