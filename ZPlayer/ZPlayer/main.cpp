#include <windows.h>
#include <tchar.h>
#pragma once
#include <UIlib.h>
using namespace DuiLib;

#pragma comment(lib, "DuiLib.lib")
#pragma comment(lib, "Veda.lib")


#include "PlayerMainUI.h"
#include "Logger.h"
Logger logger;
#include <Datetime.h>

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{

	Datetime dt;
	LOG_INFO(logger) << dt.format().c_str() << endl;

	CPaintManagerUI::SetInstance(hInstance);

	CPlayerMainUI mainUI;
	mainUI.Create(NULL, _T("ZPlayer Main UI"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
	mainUI.CenterWindow();

	MusicListItemInfo item;
	item.isFolder = false;
	item.id = _T("");
	item.title = _T("Default List");
	item.artist = _T("dddd");
	item.album = _T("kkk");
	item.isEmpty = true;
	mainUI.mMusicListCtrl->AddNode(item);
	mainUI.mMusicListCtrl->AddNode(std::move(item));

	/*MusicListItemInfo item;
	item.isFolder = true;
	item.id = _T("");
	item.title = _T("Default List");
	item.isEmpty = false;
	Node* root = mainUI.mMusicListCtrl->AddNode(std::move(item));*/

	//MusicListItemInfo item2;
	//item2.id = _T("");
	//item2.title = _T("xx");
	//item2.album = _T("±£ÏÕ");
	//item2.artist = _T("JJ");
	//item2.isFolder = true;
	//item2.isEmpty = false;
	//mainUI.mMusicListCtrl->AddNode(item2);
	//item2.isFolder = false;
	//item2.isEmpty = true;
	//mainUI.mMusicListCtrl->AddNode((item2), root);
	//mainUI.mMusicListCtrl->AddNode((item2), root);

	mainUI.ShowModal();
	return 0;
}