#include <windows.h>
#include <tchar.h>
#pragma once
#include <UIlib.h>
using namespace DuiLib;

#pragma comment(lib, "DuiLib.lib")

#include "PlayerMainUI.h"
#include "Logger.h"
Logger logger;

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	CPaintManagerUI::SetInstance(hInstance);

	CPlayerMainUI mainUI;
	mainUI.Create(NULL, _T("ZPlayer Main UI"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
	mainUI.CenterWindow();
	MusicListItemInfo item;
	item.isFolder = true;
	item.id = _T("");
	item.title = _T("Default List");
	item.isEmpty = false;
	Node* root = mainUI.mMusicListCtrl->AddNode(std::move(item));

	MusicListItemInfo item2;
	item2.id = _T("");
	item2.title = _T("xx");
	item2.album = _T("±£ÏÕ");
	item2.artist = _T("JJ");
	item2.isFolder = true;
	item2.isEmpty = false;
	mainUI.mMusicListCtrl->AddNode(item2);
	item2.isFolder = false;
	item2.isEmpty = true;
	mainUI.mMusicListCtrl->AddNode((item2), root);
	mainUI.mMusicListCtrl->AddNode((item2), root);
	mainUI.ShowModal();
	return 0;
}