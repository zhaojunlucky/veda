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
	if (_tcscmp(pstrClass, _T("PlayControl")) == 0)
	{
		return new PlayControlUI;
	}
	return NULL;
}

void CPlayerMainUI::Notify(TNotifyUI& msg)
{
	//LOG_INFO(logger) << "main ui:" << msg.sType.GetData()<< " "<<msg.pSender->GetName() << endl;
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
	else if (msg.sType == _T("itemactivate"))
	{
		CListUI* playlist = static_cast<CMusicListCtrl*>(m_PaintManager.FindControl(L"playlist"));
		if ((playlist != NULL) && playlist->GetItemIndex(msg.pSender) != -1)
		{
			if (_tcsicmp(msg.pSender->GetClass(), _T("ListContainerElementUI")) == 0)
			{
				CListContainerElementUI *playlistItem = (CListContainerElementUI*)playlist->GetItemAt(playlist->GetCurSelActivate());
				if (playlistItem != NULL)
				{
					CLabelUI* playlistName = (CLabelUI*)playlistItem->FindSubControl(L"dd");
					if (playlistName != NULL)
					{
						LOG_INFO(logger) << playlistName->GetText() << endl;
					}
				}
			}
		}
	}
	else
	{
		__super::Notify(msg);
	}
}