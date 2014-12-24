#pragma once
#include "BaseException.h"
namespace veda
{
	class VEDA_EXPORT NetException : public BaseException
	{
	public:
		NetException();
		NetException(const String& mes);
	};
}