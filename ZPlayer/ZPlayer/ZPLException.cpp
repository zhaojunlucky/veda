#include "ZPLException.h"


ZPLException::ZPLException()
{
}


ZPLException::~ZPLException()
{
}

ZPLException::ZPLException(const wchar_t* mes)
	:mMessage(mes)
{

}
ZPLException::ZPLException(const veda::String & mes)
	: mMessage(mes)
{

}
const veda::String& ZPLException::getErrorMessage() const
{
	return mMessage;
}
