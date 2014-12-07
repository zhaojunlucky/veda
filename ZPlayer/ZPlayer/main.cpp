#include <windows.h>
#include <tchar.h>
#pragma once
#include <UIlib.h>
using namespace DuiLib;

#pragma comment(lib, "DuiLib.lib")
#pragma comment(lib, "Veda.lib")
#pragma comment(lib,"Sqlite3.lib")
#pragma comment(lib,"tag.lib")

#include "PlayerMainUI.h"
#include "Logger.h"
Logger logger;
#include <Datetime.h>
#include <sqlite.h>
using namespace sqlite3;
#include <Directory.h>

#include <taglib/fileref.h>
void testWriteData()
{
	try
	{ 
		//Sqlite3Connection conn("E:\\Documents\\Projects\\GitHub\\veda\\ZPlayer\\x64\\Debug\\data\\music.db");
		//conn.open();
		//Sqlite3StatementPtr stmt = conn.prepare("INSERT INTO MUSIC_META_DATA(FULL_PATH,IS_CUE,ARTIST,ALBUM,TITLE,START_TIME,END_TIME,LAST_MODIFIED_TIME,LAST_SIZE) VALUES(?,0,?,?,?,?,?,?,?)");
		//Directory dir(L"E:\\Documents\\Musics\\Aldnoah Zero");
		//DirectoryIteratorPtr it = dir.searchFiles(L"*.wav");
		//AString str;
		//while (it->hasNext())
		//{
		//	const FileInfo & fi = it->get();
		//	str.from(fi.fullPath.c_str());
		//	TagLib::FileRef f(str.c_str());

		//	stmt->bindText(1, str.c_str(), str.getSize(), SQLITE_STATIC);
		//	stmt->bindText(2, f.tag()->artist().toCString(), f.tag()->artist().length(), SQLITE_STATIC);
		//	stmt->bindText(3, f.tag()->album().toCString(), f.tag()->album().length(), SQLITE_STATIC);
		//	stmt->bindText(4, f.tag()->title().toCString(), f.tag()->title().length(), SQLITE_STATIC);
		//	stmt->bindInt64(5, 0);
		//	stmt->bindInt64(6, f.audioProperties()->length());
		//	stmt->bindInt64(7, fi.lastModifiedTime);
		//	stmt->bindInt64(8, fi.fileSize);
		//	stmt->executeUpdate();
		//}
		//conn.close();

		//Sqlite3StatementPtr stmtQuery = conn.prepare("SELECT FULL_PATH FROM MUSIC_META_DATA");
		//Sqlite3ResultSetPtr rs = stmtQuery->executeQuery();
		//while (rs->hasNext())
		//{
		//	TagLib::FileRef f((const char*)rs->getText(0));
		//	LOG_INFO(logger) << (const char*)rs->getText(0)<<","<<f.audioProperties()->length() << endl;
		//}
		//rs->close();
		//stmtQuery->close();
		//conn.close();
		/*
		Directory dir(L"E:\\Documents\\Musics\\Aldnoah Zero");
		DirectoryIteratorPtr it = dir.searchFiles(L"*.wav");
		while (it->hasNext())
		{
			const FileInfo & fi = it->get();
			Datetime dt(fi.lastModifiedTime);
			LOG_INFO(logger) << dt.format(L"yyyy年MM月dd日HH时mm分ss秒S毫秒")->c_str() << " : "<< fi.fileSize << endl;
		}*/
	}
	catch (Sqlite3Exception &e)
	{
		LOG_INFO(logger) << e.what() << endl;
	}
}

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{

	Datetime dt;
	LOG_INFO(logger) << dt.format(L"yyyy年MM月dd日HH时mm分ss秒S毫秒")->c_str() << endl;

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

	testWriteData();

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
	return 0;
}