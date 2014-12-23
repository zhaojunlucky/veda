#include "PlayerMainUI.h"
#include <gdipluscolor.h>
#include "DbHelper.h"
#include <Sqlite3Exception.h>
#include "MusicInfoHelper.h"
#include "PlayUtil.h"

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
	mAPlayer->Stop();
	KillTimer(this->GetHWND(), 1);
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

LRESULT CPlayerMainUI::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	bool handled = false;
	switch (uMsg)
	{
	case WM_TIMER:
	{
		//LOG_INFO(logger) << L"on timer" << endl;
		onTimer();
		handled = true;
	}break;
	default:break;
	}
	if (!handled)
	{
		return WindowImplBase::HandleMessage(uMsg, wParam, lParam);
	}
	else
	{
		return S_OK;
	}
}

void CPlayerMainUI::Notify(TNotifyUI& msg)
{
	//LOG_INFO(logger) << "main ui:" << msg.sType.GetData()<< " "<<msg.pSender->GetName() << endl;
	if (msg.sType == _T("itemdbclick"))
	{
		CMusicListCtrl* musicList = static_cast<CMusicListCtrl*>(m_PaintManager.FindControl(KMUSIC_LIST_CTRL_NAME));
		auto index = musicList->GetItemIndex(msg.pSender);
		if ((musicList != NULL) && index != -1)
		{
			if (_tcsicmp(msg.pSender->GetClass(), _T("ListContainerElementUI")) == 0)
			{
				Node* node = (Node*)msg.pSender->GetTag();

				if (musicList->CanExpand(node))
				{
					musicList->SetChildVisible(node, !node->getData().childVisible);
				}
			}
			// play item index
			LOG_INFO(logger) << index << endl;
			if (mPlayIndex != index || !mAPlayer->GetPlayerState().isPlaying)
			{
				mPlayIndex = index;
				playItem((size_t)index);
			}			
			else
			{
				if (mAPlayer->GetPlayerState().isPause)
				{
					mAPlayer->Resume();
				}
				else
				{
					mAPlayer->Pause();
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
	mAPlayer = new AudioPlayer;
	CContainerUI* pPlayControl = (CContainerUI*)m_PaintManager.FindControl(L"playCtrl");
	mPlayPauseBtn = (CButtonUI*)pPlayControl->FindSubControl(L"playPause");
	mSoundBtn = (CButtonUI*)pPlayControl->FindSubControl(L"soundBtn");
	mPlayModeBtn = (CButtonUI*)pPlayControl->FindSubControl(L"playModeBtn");
	mVolumeSlider = (CSliderUI*)pPlayControl->FindSubControl(L"volumeSlider");
	mSeekSlider = (CSliderUI*)pPlayControl->FindSubControl(L"seekSlider");
	mPlaylisyCtrl = (CListUI*)m_PaintManager.FindControl(L"playlist");
	mPlayDurationCtrl = (CLabelUI*)pPlayControl->FindSubControl(L"playDuration");
	mTotalDurationCtrl = (CLabelUI*)pPlayControl->FindSubControl(L"totalDuration");
	mPlayNextBtn = (CButtonUI*)pPlayControl->FindSubControl(L"nextBtn");;
	mPlayPreviousBtn = (CButtonUI*)pPlayControl->FindSubControl(L"previousBtn");;
	updateSoundBtn();
	updatePlayMode();
	mDecoder = NULL;
	mAPlayer->SetCallback(PlayerCallback, this);

	mAPlayer->SetMute(false);
	//mAPlayer->Play();
	loadData();
	loadPlaylist();
	loadPlaylistInUI(mPlModel.getPlaylist((size_t)0));
	DragDropRegister(this->GetHWND());
	SetTimer(this->GetHWND(), 1, 900, NULL);
	mSeekSlider->SetValue(0);
	mActiveList = mPlModel.getPlaylist((size_t)0);
	// load from config
	mPlayIndex = 0;
	if (mActiveList->getPlaylistSize() > 0)
	{
		mMusicListCtrl->SelectItem(mPlayIndex, true);
	}

	// load from config
	mPlaylisyCtrl->SelectItem(0, true);
	
	updatePlayPreNext();
	updateSeekSlider(false);
}

bool CPlayerMainUI::handleClick(TNotifyUI& msg)
{
	bool handled = true;
	if (msg.pSender->GetName() == _T("playPause"))
	{
		bool play = mAPlayer->GetPlayerState().isPlaying && mAPlayer->GetPlayerState().isPause;
		updatePlayBtn(play);
		if (play)
		{
			mAPlayer->Resume();
		}
		else if (mAPlayer->GetPlayerState().isPlaying)
		{
			mAPlayer->Pause();
		}
		else
		{
			playItem(mPlayIndex);
		}
		
	}
	else if (msg.pSender->GetName() == _T("soundBtn"))
	{
		mIsMute = !mIsMute;
		updateSoundBtn();
	}
	else if (msg.pSender->GetName() == _T("playModeBtn"))
	{
		mPlayMode = (PlayMode)((mPlayMode + 1) % (PlayMode::Shuffle + 1));
		updatePlayMode();
	}
	else if (msg.pSender->GetName() == _T("nextBtn"))
	{
		playNext();
	}
	else if (msg.pSender->GetName() == _T("previousBtn"))
	{
		playPrevious();
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
		if (mAPlayer->GetPlayerState().isPlaying)
		{
			mAPlayer->Seek(mSeekSlider->GetValue() + mAPlayer->getCurrentPlayStart());
		}
	}
	else
	{
		handled = false;
	}
	return handled;
}
void CPlayerMainUI::updatePlayBtn(bool isPlay)
{
	// use click play
	PlayerStateMessage ps;
	if (isPlay)
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
	//mShowPlay = !mShowPlay;
}
void CPlayerMainUI::updateSoundBtn()
{
	if (mIsMute)
	{
		mSoundBtn->SetNormalImage(mSkinRes.SoundMuteNormal.get()->c_str());
		mSoundBtn->SetHotImage(mSkinRes.SoundMuteNormal.get()->c_str());
		mSoundBtn->SetPushedImage(mSkinRes.SoundMuteDown.get()->c_str());
		mSoundBtn->SetToolTip(L"Sound");
		mAPlayer->SetMute(true);
	}
	else
	{
		mAPlayer->SetMute(false);
		mSoundBtn->SetToolTip(L"Mute");
		int max = mVolumeSlider->GetMaxValue();
		int v = mVolumeSlider->GetValue();
		mVolumnStr = v;
		mAPlayer->SetVolumne(v / 100.0 * MAX_VOLUME);
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

void CPlayerMainUI::PlayerCallback(void* instance, PlayerStateMessage mes, void *client, WPARAM, LPARAM)
{
	CPlayerMainUI* p = (CPlayerMainUI*)client;
	bool uiUpdateFlag;
	if (mes == PlayerStateMessage::Play || mes == PlayerStateMessage::Resume)
	{
		uiUpdateFlag = true;
		p->updatePlayBtn(uiUpdateFlag);
		p->updateSeekSlider(true);
	}
	else if (mes == PlayerStateMessage::Pause || mes == PlayerStateMessage::UserStop)
	{
		if (mes == PlayerStateMessage::UserStop)
		{
			p->updateSeekSlider(false);
		}
		uiUpdateFlag = false;
		p->updatePlayBtn(uiUpdateFlag);
	}
	else if (mes == PlayerStateMessage::Stop)
	{
		p->updateSeekSlider(false);
		uiUpdateFlag = false;
		p->updatePlayBtn(uiUpdateFlag);
		p->updatePlayPreNext();
		// play next
		p->playNext();
	}
}

DROPEFFECT CPlayerMainUI::onDragEnter(HWND hwnd, IDataObject* dataObj, DWORD grfKeyState, POINT pt)
{ 
	DROPEFFECT eff = DROPEFFECT_NONE;
	FORMATETC cFmt = { (CLIPFORMAT)CF_HDROP, NULL, DVASPECT_CONTENT, -1, TYMED_HGLOBAL };
	STGMEDIUM stgmedium;
	if (dataObj->GetData(&cFmt, &stgmedium) == S_OK)
	{
		eff = DROPEFFECT_COPY;
		ReleaseStgMedium(&stgmedium);
	}
	mDropEffect = eff;
	return eff; 
}
DROPEFFECT CPlayerMainUI::onDragOver(HWND hwnd, DWORD grfKeyState, POINT pt)
{ 
	return mDropEffect;
}
void CPlayerMainUI::onDragLeave(HWND hwnd)
{

}
HRESULT CPlayerMainUI::onDrop(HWND hwnd, IDataObject* dataObj, DWORD grfKeyState, POINT pt)
{ 
	FORMATETC cFmt = { (CLIPFORMAT)CF_HDROP, NULL, DVASPECT_CONTENT, -1, TYMED_HGLOBAL };
	STGMEDIUM stgmedium;
	MusicInfoHelper musicInfoHelper;
	veda::Vector<MusicInfoPtr> vec;
	if (dataObj->GetData(&cFmt, &stgmedium) == S_OK)
	{
		HDROP hdrop = reinterpret_cast<HDROP>(stgmedium.hGlobal);
		UINT cFiles = DragQueryFile(hdrop, 0xFFFFFFFF, NULL, 0);
		for (UINT i = 0; i < cFiles; i++) {
			TCHAR szFile[MAX_PATH];
			UINT cch = DragQueryFile(hdrop, i, szFile, MAX_PATH);
			if (cch > 0 && cch < MAX_PATH) {
				LOG_INFO(logger) << szFile << endl;
				// use thread
				musicInfoHelper.parseMedia(vec, szFile);
			}
		}
		ReleaseStgMedium(&stgmedium);
	}
	DbHelper* db = DbHelper::getInstance();
	try
	{
		db->addMusics(vec);
		mPlModel.getPlaylist((size_t)0)->addMusicInfos(vec);
		for (auto& m : vec)
		{
			addMusicInUI(*m.get());
		}
		updatePlayPreNext();
	}
	catch (Sqlite3Exception& e)
	{

	}
	return S_OK;
}

void CPlayerMainUI::addPlaylistInUI(const wchar_t* name)
{
	CListContainerElementUI* lce = new CListContainerElementUI;
	lce->SetFixedHeight(33);
	CLabelUI* label = new CLabelUI;
	label->SetName(name);
	label->SetText(name);
	label->SetFixedWidth(120);
	RECT rc = {12,0,0,0};
	label->SetTextPadding(rc);
	label->SetFont(0);
	static Color textColor(0, 255, 255, 255);
	label->SetTextColor(textColor.GetValue());
	static Color disabledTextColor(255,128,128,128);
	label->SetDisabledTextColor(disabledTextColor.GetValue());
	lce->Add(label);
	mPlaylisyCtrl->Add(lce);
}

void CPlayerMainUI::addMusicInUI(const MusicInfo& musicInfo)
{
	MusicListItemInfo item;
	item.isFolder = false;
	item.id = musicInfo.id;
	item.title = musicInfo.title;
	item.artist = musicInfo.artist;
	item.album = musicInfo.album;
	item.isEmpty = true;
	mMusicListCtrl->AddNode(std::move(item));
}

void CPlayerMainUI::loadData()
{
	try
	{
		mPlModel.loadData();
	}
	catch (Sqlite3Exception& e)
	{
		LOG_ERROR(logger) << e.what() << endl;
	}
	
}
void CPlayerMainUI::loadPlaylist()
{
	auto count = mPlModel.getPlaylistCount();
	for (auto i = 0; i < count; i++)
	{
		addPlaylistInUI(mPlModel.getPlaylist(i)->getPlaylistName());
	}
}

void CPlayerMainUI::loadPlaylistInUI(Playlist* pl)
{
	size_t count = pl->getPlaylistSize();
	for (auto i = 0; i < count; i++)
	{
		addMusicInUI(pl->getMusicInfo(i));
	}
}

void CPlayerMainUI::playItem(size_t index)
{
	if (mMusicListCtrl->GetCurSel() != index)
	{
		mMusicListCtrl->SelectItem(index, true);
	}
	mAPlayer->Stop();
	if (mDecoder)
	{
		delete mDecoder;
	}
	auto& m = mPlModel.getPlaylist((size_t)0)->getMusicInfo(index);
	mDecoder = DecoderFactory::CreateDecoderByFile(m.fullPath);
	mDecoder->Open(m.fullPath);
	mAPlayer->Open(mDecoder);
	float totalTime = 0;
	if (m.isCue)
	{
		totalTime = m.end - m.start;
		mAPlayer->Play(m.start, m.end);
	}
	else
	{
		totalTime = mDecoder->getWaveInfo().durationTime;
		mAPlayer->Play();
	}
	mSeekSlider->SetMaxValue(totalTime);
	mPlayDurationCtrl->SetText(L"00:00");
	mTotalDurationCtrl->SetText(PlayUtil::formatTime(totalTime)->c_str());
}

void CPlayerMainUI::onTimer()
{
	if (mAPlayer->GetPlayerState().isPlaying && !mAPlayer->GetPlayerState().isPause)
	{
		auto duration = mAPlayer->GetPlayDuration() - mAPlayer->getCurrentPlayStart();
		mSeekSlider->SetValue(duration);
		mPlayDurationCtrl->SetText(PlayUtil::formatTime(duration)->c_str());
	}	
}

void CPlayerMainUI::playNext()
{
	if (canPlayNext())
	{
		if (mPlayMode == PlayMode::RepeatAll)
		{
			mPlayIndex = (++mPlayIndex) % mActiveList->getPlaylistSize();
		}
		else
		{
			mPlayIndex = PlayUtil::getRandomNext(mActiveList->getPlaylistSize());
		}
		playItem(mPlayIndex);
	}
}
void CPlayerMainUI::playPrevious()
{
	if (canPlayPrevious())
	{
		if (mPlayMode == PlayMode::RepeatAll)
		{
			mPlayIndex = ((--mPlayIndex) + mActiveList->getPlaylistSize()) % mActiveList->getPlaylistSize();
		}
		else
		{
			mPlayIndex = PlayUtil::getRandomNext(mActiveList->getPlaylistSize());
		}
		playItem(mPlayIndex);
	}
}
bool CPlayerMainUI::canPlayNext()
{
	auto next = mActiveList->getPlaylistSize() > 0;
	
	return next;
}
bool CPlayerMainUI::canPlayPrevious()
{
	auto previous = mActiveList->getPlaylistSize() > 0;

	return previous;
}

bool CPlayerMainUI::canPlay()
{
	auto play = mActiveList->getPlaylistSize() > 0;

	return play;
}

void CPlayerMainUI::updatePlayPreNext()
{
	mPlayNextBtn->SetEnabled(canPlayNext());
	mPlayPreviousBtn->SetEnabled(canPlayPrevious());
	mPlayPauseBtn->SetEnabled(canPlay());
}

void CPlayerMainUI::updateSeekSlider(bool enable)
{
	mSeekSlider->SetEnabled(enable);
	mPlayDurationCtrl->SetVisible(enable);
	mTotalDurationCtrl->SetVisible(enable);
}