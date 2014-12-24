#pragma once
#include "veda.h"
#include "ZString.h"
namespace veda
{
	class VEDA_EXPORT BaseException
	{
	public:
		BaseException();
		BaseException(const String& mes);

		const String& getMessage();
		BaseException& operator=(const BaseException& mes);
	protected:
		String mExMes;
	};
}