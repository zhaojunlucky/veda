#include "stdafx.h"
#include "NetException.h"
namespace veda
{
	NetException::NetException()
		:BaseException()
	{

	}
	NetException::NetException(const String& mes)
		: BaseException(mes)
	{

	}
}