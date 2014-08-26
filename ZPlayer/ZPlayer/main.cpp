#include <windows.h>
#include <tchar.h>
#pragma once
#include <UIlib.h>
using namespace DuiLib;

#pragma comment(lib, "DuiLib.lib")

#include "PlayerMainUI.h"


int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	CPaintManagerUI::SetInstance(hInstance);

	CPlayerMainUI mainUI;
	mainUI.Create(NULL, _T("ZPlayer Main UI"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
	mainUI.CenterWindow();
	mainUI.ShowModal();
	return 0;
}