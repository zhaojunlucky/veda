#include "stdafx.h"
#include "UIToolKits.h"
#include <uxtheme.h>
#include <dwmapi.h>
#include <htmlayout.h>

namespace zhui
{
	UIToolKits::UIToolKits()
	{
	}


	UIToolKits::~UIToolKits()
	{
	}

	bool UIToolKits::IsAreoEnabled()
	{
		if (CanEnableAreo())
		{
			BOOL bDwm;
			DwmIsCompositionEnabled(&bDwm);
			return (TRUE == bDwm);
		}
		return false;
	}

	bool UIToolKits::CanEnableAreo()
	{
		OSVERSIONINFO osVersion;
		ZeroMemory(&osVersion, sizeof(OSVERSIONINFO));
		osVersion.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

		GetVersionEx(&osVersion);

		if (osVersion.dwMajorVersion < 6) return false;

		return true;
	}

	HRESULT UIToolKits::EnableBlurBehind(HWND hwnd)
	{
		HRESULT hr = S_OK;

		//Create and populate the BlurBehind structre
		DWM_BLURBEHIND bb = { 0 };
		//Disable Blur Behind and Blur Region;
		bb.dwFlags = DWM_BB_ENABLE;
		bb.fEnable = true;
		bb.hRgnBlur = NULL;

		//Disable Blur Behind
		hr = DwmEnableBlurBehindWindow(hwnd, &bb);
		if (SUCCEEDED(hr))
		{
			//do more things
		}
		return hr;
	}


	HRESULT  UIToolKits::SetAeroTransparentBack(HWND hwnd)
	{
		// Negative margins have special meaning to DwmExtendFrameIntoClientArea.
		// Negative margins create the "sheet of glass" effect, where the client area
		//  is rendered as a solid surface with no window border.
		MARGINS margins = { -1 };
		HRESULT hr = S_OK;
		// Extend frame across entire window.
		hr = DwmExtendFrameIntoClientArea(hwnd, &margins);
		if (SUCCEEDED(hr))
		{
			// if succeeded configure htmlayout to draw on base with alpha. 
			HTMLayoutSetOption(hwnd, HTMLAYOUT_TRANSPARENT_WINDOW, TRUE);
		}
		return hr;
	}
}