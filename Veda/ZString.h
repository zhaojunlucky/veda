#pragma once
#include "BasicString.h"
namespace veda
{
	typedef BasicString<WcharTraits, char> WString;
	typedef BasicString<CharTraits, wchar_t> AString;
#ifdef _UNICODE
	typedef WString String;
	typedef WcharTraits::value_type tchar;
#else
	typedef AString String;
	typedef WcharTraits::value_type tchar;
#endif

	std::ostream& operator<<(std::ostream& os, const AString& dt)
	{
		os << dt.c_str();
		return os;
	}
	std::wostream& operator<<(std::wostream& os, const WString& dt)
	{
		os << dt.c_str();
		return os;
	}
}

