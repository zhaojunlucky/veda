#pragma once
#include "ZString.h"
namespace veda
{
	class BaseException
	{
	public:
		BaseException();
		BaseException(const String& mes);

		const String& getMessage();
		BaseException& operator=(const BaseException& mes);
	protected:
		String mExMes;
	};

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