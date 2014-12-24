#include "stdafx.h"
#include "BaseException.h"

namespace veda
{
	BaseException::BaseException()
	{

	}
	BaseException::BaseException(const String& mes)
		:mExMes(mes)
	{

	}

	const String& BaseException::getMessage()
	{
		return mExMes;
	}

	BaseException& BaseException::operator = (const BaseException& mes)
	{
		if (this != &mes)
		{
			mExMes = mes.mExMes;
		}
		return *this;
	}
}