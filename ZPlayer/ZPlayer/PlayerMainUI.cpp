#include "PlayerMainUI.h"

const TCHAR* const KMUSIC_LIST_CTRL_NAME = _T("musicList");
CPlayerMainUI::CPlayerMainUI()
{
	mShowPlay = true;
	// load from config
	mIsMute = false;
	mPlayMode = PlayMode::RepeatAll;
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
	else if (msg.sType == _T("click"))
	{
		if (!handleClick(msg))
		{
			__super::Notify(msg);
		}
	}
	else if (msg.sType == _T("valuechanged"))
	{
		if (!handleSliderAndProgress(msg))
		{
			__super::Notify(msg);
		}
	}
	else
	{
		__super::Notify(msg);
	}
}

void CPlayerMainUI::InitWindow()
{
	CContainerUI* pPlayControl = (CContainerUI*)m_PaintManager.FindControl(L"playCtrl");
	mPlayPauseBtn = (CButtonUI*)pPlayControl->FindSubControl(L"playPause");
	mSoundBtn = (CButtonUI*)pPlayControl->FindSubControl(L"soundBtn");
	mPlayModeBtn = (CButtonUI*)pPlayControl->FindSubControl(L"playModeBtn");
	mVolumeSlider = (CSliderUI*)pPlayControl->FindSubControl(L"volumeSlider");
	mSeekSlider = (CSliderUI*)pPlayControl->FindSubControl(L"seekSlider");
	updateSoundBtn();
	updatePlayMode();
}

bool CPlayerMainUI::handleClick(TNotifyUI& msg)
{
	bool handled = true;
	if (msg.pSender->GetName() == _T("playPause"))
	{
		updatePlayBtn();
	}
	else if (msg.pSender->GetName() == _T("soundBtn"))
	{
		mIsMute = !mIsMute;
		updateSoundBtn();
	}
	else if (msg.pSender->GetName() == _T("playModeBtn"))
	{
		mPlayMode = (PlayMode)((mPlayMode + 1) % (PlayMode::Shuffle+1));
		updatePlayMode();
	}
	else
	{
		handled = false;
	}
	return handled;
}

bool CPlayerMainUI::handleSliderAndProgress(TNotifyUI& msg)
{
	bool handled = true;
	if (msg.pSender->GetName() == _T("volumeSlider"))
	{
		mIsMute = false;
		updateSoundBtn();
	}
	else if (msg.pSender->GetName() == _T("seekSlider"))
	{

	}
	else
	{
		handled = false;
	}
	return handled;
}
void CPlayerMainUI::updatePlayBtn()
{
	// use click play
	PlayerStateMessage ps;
	if (mShowPlay)
	{
		// play, then set pause img
		ps = PlayerStateMessage::Play;
		mPlayPauseBtn->SetNormalImage(mSkinRes.PauseNormal.get()->c_str());
		mPlayPauseBtn->SetHotImage(mSkinRes.PauseNormal.get()->c_str());
		mPlayPauseBtn->SetPushedImage(mSkinRes.PauseDown.get()->c_str());
		mPlayPauseBtn->SetToolTip(L"Pause");
	}
	else
	{
		// pause, then set play img
		ps = PlayerStateMessage::Pause;
		mPlayPauseBtn->SetNormalImage(mSkinRes.PlayNormal.get()->c_str());
		mPlayPauseBtn->SetHotImage(mSkinRes.PlayNormal.get()->c_str());
		mPlayPauseBtn->SetPushedImage(mSkinRes.PlayDown.get()->c_str());
		mPlayPauseBtn->SetToolTip(L"Play");
	}
	mShowPlay = !mShowPlay;
}
void CPlayerMainUI::updateSoundBtn()
{
	if (mIsMute)
	{
		mSoundBtn->SetNormalImage(mSkinRes.SoundMuteNormal.get()->c_str());
		mSoundBtn->SetHotImage(mSkinRes.SoundMuteNormal.get()->c_str());
		mSoundBtn->SetPushedImage(mSkinRes.SoundMuteDown.get()->c_str());
		mSoundBtn->SetToolTip(L"Sound");
	}
	else
	{
		mSoundBtn->SetToolTip(L"Mute");
		int max = mVolumeSlider->GetMaxValue();
		int v = mVolumeSlider->GetValue();
		mVolumnStr = v;
		mVolumeSlider->SetToolTip(mVolumnStr.c_str());
		if (v >= 30 && v < 60)
		{
			mSoundBtn->SetNormalImage(mSkinRes.SoundMiddleNormal.get()->c_str());
			mSoundBtn->SetHotImage(mSkinRes.SoundMiddleNormal.get()->c_str());
			mSoundBtn->SetPushedImage(mSkinRes.SoundMiddleDown.get()->c_str());
		}
		else if (v <= 0)
		{
			mSoundBtn->SetNormalImage(mSkinRes.SoundMinNormal.get()->c_str());
			mSoundBtn->SetHotImage(mSkinRes.SoundMinNormal.get()->c_str());
			mSoundBtn->SetPushedImage(mSkinRes.SoundMinDown.get()->c_str());
		}
		else if (v < 30)
		{
			mSoundBtn->SetNormalImage(mSkinRes.SoundLowNormal.get()->c_str());
			mSoundBtn->SetHotImage(mSkinRes.SoundLowNormal.get()->c_str());
			mSoundBtn->SetPushedImage(mSkinRes.SoundLowDown.get()->c_str());
		}
		else if (v >= 60)
		{
			mSoundBtn->SetNormalImage(mSkinRes.SoundMaxNormal.get()->c_str());
			mSoundBtn->SetHotImage(mSkinRes.SoundMaxNormal.get()->c_str());
			mSoundBtn->SetPushedImage(mSkinRes.SoundMaxDown.get()->c_str());
		}
	}
}

void CPlayerMainUI::updatePlayMode()
{
	if (mPlayMode == PlayMode::RepeatAll)
	{
		mPlayModeBtn->SetNormalImage(mSkinRes.RepeatAllNormal.get()->c_str());
		mPlayModeBtn->SetHotImage(mSkinRes.RepeatAllNormal.get()->c_str());
		mPlayModeBtn->SetPushedImage(mSkinRes.RepeatAllDown.get()->c_str());
		mPlayModeBtn->SetToolTip(L"Shuffle");
	}
	else if (mPlayMode == PlayMode::Shuffle)
	{
		mPlayModeBtn->SetNormalImage(mSkinRes.ShuffleNormal.get()->c_str());
		mPlayModeBtn->SetHotImage(mSkinRes.ShuffleNormal.get()->c_str());
		mPlayModeBtn->SetPushedImage(mSkinRes.ShuffleDown.get()->c_str());
		mPlayModeBtn->SetToolTip(L"Repeat All");
	}
}
