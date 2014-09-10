#pragma once
#include <Windows.h>
#include <Vector.h>


namespace veda
{
	class StringConvert
	{
	public:
		StringConvert();
		~StringConvert();
		const wchar_t* char2wchar(const char* str);
		const char* wchar2char(const wchar_t* str);
	private:
		Vector<char> chars;
		Vector<wchar_t> wchars;
	};
}


