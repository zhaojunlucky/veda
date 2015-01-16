#pragma once
#include <windows.h>
#include <tchar.h>

#include <UIlib.h>
using namespace DuiLib;

#pragma comment(lib,"ZAudio.lib")
#pragma comment(lib,"ZPEngine.lib")
#pragma comment(lib, "DuiLib.lib")
#pragma comment(lib, "Veda.lib")
#pragma comment(lib,"Sqlite3.lib")
#pragma comment(lib,"tag.lib")
#pragma comment(lib,"Algorithm.lib")
#include "PlayerMainUI.h"
#include <Logger.h>
Logger logger;
#include <Datetime.h>
#include <Directory.h>
#include "CueSheet.h"
#include <FileUtil.h>
using namespace veda;
#include <string>
#include <hash_map>

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	veda::String str = L"test hash code";
	std::wstring str2 = L"test hash code";
	std::hash_map<veda::String, bool> d;
	d[str] = true;
	std::hash<wstring> h;
	LOG_INFO(logger) << L"veda::String=" << str.hashcode() << L", wstring=" << h(str2) << endl;
	CoInitialize(NULL);
	OleInitialize(NULL);
	//Datetime dt;
	//LOG_INFO(logger) << dt.format(L"yyyy年MM月dd日HH时mm分ss秒S毫秒")->c_str() << endl;
	CPaintManagerUI::SetInstance(hInstance);
	CPlayerMainUI mainUI;
	mainUI.Create(NULL, _T("JJ Forever"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
	mainUI.CenterWindow();
	//MusicListItemInfo item;
	//item.isFolder = false;
	//item.id = _T("");
	//item.title = _T("now playing");
	//item.artist = _T("now playing");
	//item.album = _T("now playing");
	//item.isEmpty = true;
	//mainUI.mMusicListCtrl->AddNode(item);
	//mainUI.mMusicListCtrl->AddNode(std::move(item));
	/*CueSheet cue;
	auto str = L"C:\\Users\\i076777\\Desktop\\Musics\\[140910]TVアニメ「アルドノア・ゼロ」ED『AZaLIEz』SawanoHiroyuki[nZk](期間生産限定アニメ盤)(DVD付)\\SawanoHiroyuki[nZk] - AZaLIEz.cue";
	AString tmp;
	tmp.from(str);
	LOG_INFO(logger) << tmp.c_str() << endl;*/
	/*cue.parse(L"C:\\Users\\Jun\\Downloads\\杨千嬅.-.[狼来了].专辑.(APE).cue");*/
	//cue.parse(L"C:\\Users\\i076777\\Desktop\\Musics\\[140910]TVアニメ「アルドノア・ゼロ」ED『AZaLIEz』SawanoHiroyuki[nZk](期間生産限定アニメ盤)(DVD付)\\SawanoHiroyuki[nZk] - AZaLIEz.cue");
	/*MusicListItemInfo item;
	item.isFolder = true;
	item.id = _T("");
	item.title = _T("Default List");
	item.isEmpty = false;
	Node* root = mainUI.mMusicListCtrl->AddNode(std::move(item));*/

	//MusicListItemInfo item2;
	//item2.id = _T("");
	//item2.title = _T("xx");
	//item2.album = _T("保险");
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