#pragma once
#include <ZHtmlForm.h>
#include <memory>
#include "EventArgs.h"
#include "ZHSelectCtrl.h"
#include "PlayerController.h"
#include "MusicDataController.h"
#include "ThemeModel.h"
#include <string>
#include "ConfigController.h"
#include "ThemeController.h"

using namespace zhui;
namespace zpl
{
	class MainForm :
		public ZHtmlForm
	{
	public:
		MainForm(HINSTANCE instance, const wchar_t* htmlRes, const ZFormPara& formPara, const wchar_t* title);
		virtual ~MainForm();

	private:
		void OnButtonClick(HELEMENT he, const BEHAVIOR_EVENT_PARAMS& params);
		void OnMouseDown(HELEMENT he, const MOUSE_PARAMS& params, bool handled);
		void OnMouseDoubleClick(HELEMENT he, const MOUSE_PARAMS& params, bool handled);
	private:
		void PlayPauseClick(BehaviorEventArgs& be);
		void OnSeekDuration(float percentage);
		void OnVolumn(float percentage);
		void OnPreviousClick(BehaviorEventArgs& be);
		void OnNextClick(BehaviorEventArgs& be);
		void OnChangePlayList(MouseEventArgs& me, htmlayout::dom::element& ele);
		void OnPlayItem(MouseEventArgs& me, htmlayout::dom::element& ele);
		const MediaModel& GetMedia(const string& plName, int index);
		static void PlayerCallback(void* instance, PlayerStateMessage mes, void *client, WPARAM, LPARAM);
		/*
		 * 1. load last state from database
		 * 2. load data from database and update ui
		 */
		void Init();
		// only call this function when app init
		void UpdatePlayList();
		// when change playlist will call this func
		void UpdatePlayListMusic(const string& name);
	private:
		Point durationBar;
		int durationBarWidth;
		htmlayout::dom::element durationProgress;
		// play list control
		ZHSelectCtrl mListCtrl;
		// play list relative music list ctrl
		ZHSelectCtrl mMusicListCtrl;
		// player controller
		std::shared_ptr<PlayerController> mPlayerController;
		// music data controller
		MusicDataController mMusicDataController;
		// config controller
		ConfigController mConfigController;
		// theme controller
		ThemeController mThemeController;
		// current play list
		std::string mPlayListName;
		// current display list
		std::string mDisplayListName;
		bool mPlay;
		int mPlayMode;
		int mCurPlayIndex;
	};

}