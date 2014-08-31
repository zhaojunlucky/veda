#include "PlayerMainUI.h"


CPlayerMainUI::CPlayerMainUI()
{
}


CPlayerMainUI::~CPlayerMainUI()
{
}

CControlUI* CPlayerMainUI::CreateControl(LPCTSTR pstrClass)
{
	if (_tcsicmp(pstrClass, _T("MusicListCtrl")) == 0)
	{
		mMusicListCtrl = new CMusicListCtrl(m_PaintManager);
		return mMusicListCtrl;
	}
	return NULL;
}