#pragma once
#include "BaseException.h"
namespace veda
{
	class NetException : public BaseException
	{
	public:
		NetException();
		NetException(const String& mes);
	};

	NetException::NetException()
		:BaseException()
	{

	}
	NetException::NetException(const String& mes)
		:BaseException(mes)
	{

	}
}