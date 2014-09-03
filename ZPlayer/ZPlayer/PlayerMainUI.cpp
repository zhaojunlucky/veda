#include "PlayerMainUI.h"

const TCHAR* const KMUSIC_LIST_CTRL_NAME = _T("musicList");
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

void CPlayerMainUI::Notify(TNotifyUI& msg)
{
	LOG_INFO(logger) << "main ui:" << msg.sType.GetData() << endl;
	if (msg.sType == _T("itemclick"))
	{
		CMusicListCtrl* musicList = static_cast<CMusicListCtrl*>(m_PaintManager.FindControl(KMUSIC_LIST_CTRL_NAME));
		if ((musicList != NULL) && musicList->GetItemIndex(msg.pSender) != -1)
		{
			if (_tcsicmp(msg.pSender->GetClass(), _T("ListContainerElementUI")) == 0)
			{
				Node* node = (Node*)msg.pSender->GetTag();

				if (musicList->CanExpand(node))
				{
					musicList->SetChildVisible(node, !node->getData().childVisible);
				}
			}
		}
	}
	else
	{
		LOG_INFO(logger) << msg.sType << endl;
		__super::Notify(msg);
	}
}