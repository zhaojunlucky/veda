#pragma once
#include <ZString.h>

class ZPLException
{
public:
	ZPLException();
	ZPLException(const wchar_t* mes);
	ZPLException(const veda::String & mes);
	const veda::String& getErrorMessage() const;
	~ZPLException();
private:
	veda::String mMessage;
};

