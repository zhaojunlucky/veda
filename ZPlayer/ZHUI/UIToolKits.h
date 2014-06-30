#pragma once
#include <Windows.h>

namespace zhui
{
	class __declspec(dllexport) UIToolKits
	{
	public:
		UIToolKits();
		virtual ~UIToolKits();
		bool IsAreoEnabled();
		bool CanEnableAreo();
		HRESULT EnableBlurBehind(HWND hwnd);
		HRESULT  SetAeroTransparentBack(HWND hwnd);
	};
}


