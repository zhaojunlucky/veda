#pragma once
#include <UIlib.h>
using namespace DuiLib;
#include "MusicListCtrl.h"
#include "PlayControl.h"
#include "SkinResource.h"
#include "Logger.h"
#include "Base.h"
#include <PlayerBase.h>
using namespace audio::player;

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
	virtual void InitWindow();
	virtual CControlUI* CreateControl(LPCTSTR pstrClass);
	void Notify(TNotifyUI& msg);
	bool handleClick(TNotifyUI& msg);
	bool handleSliderAndProgress(TNotifyUI& msg);
	void updatePlayBtn();
	void updateSoundBtn();
	void updatePlayMode();
public:
	PlayMode mPlayMode;
	CMusicListCtrl* mMusicListCtrl;
	SkinResource mSkinRes;
	bool mShowPlay;
	bool mIsMute;
	CButtonUI* mPlayPauseBtn;
	CButtonUI* mSoundBtn;
	CButtonUI* mPlayModeBtn;
	CSliderUI* mVolumeSlider;
	CSliderUI* mSeekSlider;
	String mVolumnStr;
};

