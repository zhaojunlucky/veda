#pragma once
#include "ZString.h"
namespace veda
{
	class ErrorUtil
	{
	public:
		ErrorUtil();
		~ErrorUtil();
		static StringPtr getErrorMessage(DWORD errCode);
	};

}

