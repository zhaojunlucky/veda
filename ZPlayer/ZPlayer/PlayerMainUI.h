#pragma once
#include <UIlib.h>
using namespace DuiLib;

class CPlayerMainUI :
	public WindowImplBase
{
public:
	CPlayerMainUI();
	~CPlayerMainUI();

	virtual LPCTSTR    GetWindowClassName() const   { return _T("PlayerMainUI"); }
	virtual CDuiString GetSkinFile()                { return _T("ui/player.xml"); }
	virtual CDuiString GetSkinFolder()              { return _T(""); }
};

