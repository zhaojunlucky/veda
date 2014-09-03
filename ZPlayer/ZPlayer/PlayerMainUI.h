#pragma once
#include <UIlib.h>
using namespace DuiLib;
#include "MusicListCtrl.h"
#include "Logger.h"
extern Logger logger;
class CPlayerMainUI :
	public WindowImplBase
{
public:
	CPlayerMainUI();
	~CPlayerMainUI();

	virtual LPCTSTR    GetWindowClassName() const   { return _T("PlayerMainUI"); }
	virtual CDuiString GetSkinFile()                { return _T("ui/player.xml"); }
	virtual CDuiString GetSkinFolder()              { return _T(""); }
protected:
	virtual CControlUI* CreateControl(LPCTSTR pstrClass);
	void Notify(TNotifyUI& msg);
public:
	CMusicListCtrl* mMusicListCtrl;
};

