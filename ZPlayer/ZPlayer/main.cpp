#include <windows.h>
#include <tchar.h>
#pragma once
#include <UIlib.h>
using namespace DuiLib;

#pragma comment(lib,"ZAudio.lib")
#pragma comment(lib,"ZPEngine.lib")
#pragma comment(lib, "DuiLib.lib")
#pragma comment(lib, "Veda.lib")
#pragma comment(lib,"Sqlite3.lib")
#pragma comment(lib,"tag.lib")

#include "PlayerMainUI.h"
#include "Logger.h"
Logger logger;
#include <Datetime.h>
#include <Directory.h>
#include "CueSheet.h"

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	CoInitialize(NULL);
	OleInitialize(NULL);
	Datetime dt;
	LOG_INFO(logger) << dt.format(L"yyyy��MM��dd��HHʱmm��ss��S����")->c_str() << endl;

	CPaintManagerUI::SetInstance(hInstance);

	CPlayerMainUI mainUI;
	mainUI.Create(NULL, _T("ZPlayer Main UI"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
	mainUI.CenterWindow();

	MusicListItemInfo item;
	item.isFolder = false;
	item.id = _T("");
	item.title = _T("now playing");
	item.artist = _T("now playing");
	item.album = _T("now playing");
	item.isEmpty = true;
	mainUI.mMusicListCtrl->AddNode(item);
	mainUI.mMusicListCtrl->AddNode(std::move(item));
	CueSheet cue;
	cue.parse(L"C:\\Users\\Jun\\Downloads\\��ǧ��.-.[������].ר��.(APE).cue");

	/*MusicListItemInfo item;
	item.isFolder = true;
	item.id = _T("");
	item.title = _T("Default List");
	item.isEmpty = false;
	Node* root = mainUI.mMusicListCtrl->AddNode(std::move(item));*/

	//MusicListItemInfo item2;
	//item2.id = _T("");
	//item2.title = _T("xx");
	//item2.album = _T("����");
	//item2.artist = _T("JJ");
	//item2.isFolder = true;
	//item2.isEmpty = false;
	//mainUI.mMusicListCtrl->AddNode(item2);
	//item2.isFolder = false;
	//item2.isEmpty = true;
	//mainUI.mMusicListCtrl->AddNode((item2), root);
	//mainUI.mMusicListCtrl->AddNode((item2), root);
	mainUI.ShowModal();
	//OleUninitialize();
	//CoUninitialize();
	return 0;
}