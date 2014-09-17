#pragma once
#include <memory>
#include "BasicString.h"
namespace veda
{
	typedef BasicString<WcharTraits, char> WString;
	typedef BasicString<CharTraits, wchar_t> AString;
	
#define makeAStringPtr std::make_shared<AString>
#define makeWStringPtr std::make_shared<WString>
	typedef std::shared_ptr<WString> WStringPtr;
	typedef std::shared_ptr<AString> AStringPtr;
#ifdef _UNICODE
	typedef WString String;
	typedef WcharTraits::value_type tchar;
	typedef WStringPtr StringPtr;
#define makeStringPtr makeWStringPtr
#else
	typedef AString String;
	typedef WcharTraits::value_type tchar;
	typedef AStringPtr StringPtr;
#define makeStringPtr makeAStringPtr
#endif

	static std::ostream& operator<<(std::ostream& os, const AString& dt)
	{
		os << dt.c_str();
		return os;
	}
	static std::wostream& operator<<(std::wostream& os, const WString& dt)
	{
		os << dt.c_str();
		return os;
	}
}

