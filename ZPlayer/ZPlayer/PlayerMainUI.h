#pragma once
#include <UIlib.h>
using namespace DuiLib;
#include "MusicListCtrl.h"
#include "PlayControl.h"
#include "SkinResource.h"
#include "Logger.h"
#include "Base.h"
#include <PlayerBase.h>
#include <AudioPlayer.h>
using namespace audio::player;
#include <Decoder.h>
#include <DecoderFactory.hpp>
using namespace audio;
#include "DropTargetBase.h"
#include "PlaylistModel.h"

extern Logger logger;
class CPlayerMainUI :
	public WindowImplBase, public CDropTargetBase
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
	//virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	void Notify(TNotifyUI& msg);
	bool handleClick(TNotifyUI& msg);
	bool handleSliderAndProgress(TNotifyUI& msg);
	void updatePlayBtn();
	void updateSoundBtn();
	void updatePlayMode();
	static void __stdcall PlayerCallback(void* instance, PlayerStateMessage mes, void *client, WPARAM, LPARAM);

	virtual DROPEFFECT onDragEnter(HWND hwnd, IDataObject* dataObj, DWORD grfKeyState, POINT pt);
	virtual DROPEFFECT onDragOver(HWND hwnd, DWORD grfKeyState, POINT pt);
	virtual void onDragLeave(HWND hwnd);
	virtual HRESULT onDrop(HWND hwnd, IDataObject* dataObj, DWORD grfKeyState, POINT pt);
private:
	void addPlaylistInUI(const wchar_t* name);
	void loadData();
	void loadPlaylist();
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
	CListUI* mPlaylisyCtrl;
	String mVolumnStr;
	AudioPlayer *mAPlayer;
	Decoder* mDecoder;
	DROPEFFECT mDropEffect;
	PlaylistModel mPlModel;
};

