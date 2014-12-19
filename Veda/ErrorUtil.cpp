#include "stdafx.h"
#include "ErrorUtil.h"

namespace veda
{
	ErrorUtil::ErrorUtil()
	{
	}


	ErrorUtil::~ErrorUtil()
	{
	}

	StringPtr ErrorUtil::getErrorMessage(DWORD errCode)
	{
		LPWSTR lpBuffer = NULL;
		FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |
			FORMAT_MESSAGE_IGNORE_INSERTS |
			FORMAT_MESSAGE_FROM_SYSTEM,
			NULL,
			errCode, // 此乃错误代码，通常在程序中可由 GetLastError()得之
			LANG_NEUTRAL,
			(LPTSTR)& lpBuffer,
			0,
			NULL);
		auto  error = makeStringPtr(lpBuffer ? (lpBuffer) : (L"Error code not found!"));
		if (lpBuffer)
		{
			LocalFree(lpBuffer);
		}

		return error;
	}
}
