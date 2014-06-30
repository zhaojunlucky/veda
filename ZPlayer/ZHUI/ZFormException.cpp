#include "stdafx.h"
#include "ZFormException.h"

namespace zhui
{
	ZFormException::ZFormException(const char* message)
		:std::exception(message)
	{
	}


	ZFormException::~ZFormException()
	{
	}
}