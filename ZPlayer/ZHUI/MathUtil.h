#pragma once
#include <Windows.h>

namespace zhui
{
	template <class T>
	class __declspec(dllexport) MathUtil
	{
	public:
		static 	wchar_t* MathUtil<T>::Numeric2Str(wchar_t* buf, const wchar_t* format, T v)
		{
			wsprintf(buf, format, v);
			return buf;
		}
	};
}



