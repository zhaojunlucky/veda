#include "stdafx.h"
#include "MainForm.h"
#include <iostream>
#include <string>
#include <ZHSelectCtrl.h>s
using namespace std;

namespace zpl
{

	MainForm::MainForm(HINSTANCE instance, const wchar_t* htmlRes, const ZFormPara& formPara, const wchar_t* title)
		:ZHtmlForm(instance, htmlRes, formPara, title)
	{
		mMusicDataController.LoadDataFromDb();
		// init player controler
		mPlayerController.reset(new PlayerController);
		mPlayerController->GetPlayer()->SetCallback(&this->PlayerCallback, this);
		this->ButtonClick = std::bind<void>(&MainForm::OnButtonClick, this, std::placeholders::_1, std::placeholders::_2);
		this->MouseDown = std::bind<void>(&MainForm::OnMouseDown, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
		this->MouseDoubleClick = std::bind<void>(&MainForm::OnMouseDoubleClick, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
		htmlayout::dom::element el = GetRoot().get_element_by_id(L"progressBar");
		durationBar.x = el.get_location().left;
		durationBar.y = el.get_location().top;
		durationBarWidth = el.get_location().right - el.get_location().left;
		durationProgress = GetRoot().get_element_by_id(L"progressSlider");
		mListCtrl = GetRoot().get_element_by_id(L"playlist");
		mMusicListCtrl = GetRoot().get_element_by_id(L"content");
		// load music data from database
		Init();

		mPlay = true;
		mCurPlayIndex = 0;

	}


	MainForm::~MainForm()
	{
	}

	void MainForm::OnButtonClick(HELEMENT he, const BEHAVIOR_EVENT_PARAMS& params)
	{
		BehaviorEventArgs be(he, params);

		if (be.IsId(L"playPause"))
		{
			PlayPauseClick(be);
		}
		else if (be.IsId(L"volumn"))
		{
			float max = _wtof(be.el.get_attribute("max"));
			float v = _wtof(be.el.get_attribute("value"));
			OnVolumn(v / max);
		}
		else if (be.IsId(L"playMode"))
		{
			//uiManager->SwitchPlayMode(be);
			//cout << uiManager->GetPlayCycleMode() << endl;
		}
		else if (be.IsId(L"previous"))
		{
			OnPreviousClick(be);
		}
		else if (be.IsId(L"next"))
		{
			OnNextClick(be);
		}
	}

	void MainForm::OnMouseDown(HELEMENT he, const MOUSE_PARAMS& params, bool handled)
	{
		MouseEventArgs me(params.target, params);
		if (me.IsId(L"progressBar") || me.IsId(L"progressSlider"))
		{
			int len = params.pos.x - durationBar.x;
			OnSeekDuration((float)len / (float)durationBarWidth);
			wchar_t buf[10];
			wsprintf(buf, L"%dpx", len);
			durationProgress.set_style_attribute("width", buf);
		}
	}


	void MainForm::OnMouseDoubleClick(HELEMENT he, const MOUSE_PARAMS& params, bool handled)
	{
		// text->div->li
		MouseEventArgs me(params.target, params);

		htmlayout::dom::element d = me.el.parent();
		htmlayout::dom::element e = d.parent();
		htmlayout::dom::element f = e.parent();
		const wchar_t* id = f.get_attribute("id");
		if (id != NULL)
		{
			if (wcsicmp(id, L"playlist") == 0)
			{
				OnChangePlayList(me, f);
			}
			else if (wcsicmp(id, L"content") == 0)
			{
				OnPlayItem(me, f);
			}
		}
	}


	void MainForm::PlayPauseClick(BehaviorEventArgs& be)
	{
		cout << (mPlay ? "Play" : "Pause") << endl;
		mPlay ? mPlayerController->GetPlayer()->Play() : mPlayerController->GetPlayer()->Pause();
		mPlay = !mPlay;
		be.el.set_style_attribute("background", mPlay ? mThemeController.GetTheme().playCSSImg.c_str() : mThemeController.GetTheme().pauseCSSImg.c_str());
	}

	void MainForm::OnSeekDuration(float percentage)
	{
		cout << "seek:" << percentage << endl;
		mPlayerController->Seek(percentage);
	}

	void MainForm::OnVolumn(float percentage)
	{
		cout << "volumn:" << percentage << endl;
		mPlayerController->SetVolumn(percentage);
	}

	const MediaModel& MainForm::GetMedia(const string& plName, int delta)
	{
		const MusicListModel& musicList = mMusicDataController.GetMusicList(plName);

		mCurPlayIndex = (mCurPlayIndex + delta + musicList.MusicCount()) % musicList.MusicCount();
		return musicList.GetMedia(mCurPlayIndex);
	}

	void MainForm::OnPreviousClick(BehaviorEventArgs& be)
	{
		cout << "previous" << endl;
		// 
		mPlayerController->Play(GetMedia(mPlayListName,-1));
 	}
	void MainForm::OnNextClick(BehaviorEventArgs& be)
	{
		cout << "next" << endl;
		//
		mPlayerController->Play(GetMedia(mPlayListName, 1));
	}

	void MainForm::OnChangePlayList(MouseEventArgs& me, htmlayout::dom::element& ele)
	{
		cout << "change list" << endl;
		const PlayListModel pl = mMusicDataController.GetPlayListData(mListCtrl.getSelectItemIndex());
		UpdatePlayListMusic(pl.name);
		mDisplayListName = pl.name;
	}
	void MainForm::OnPlayItem(MouseEventArgs& me, htmlayout::dom::element& ele)
	{
		cout << "play item" << endl;
		const PlayListModel pl = mMusicDataController.GetPlayListData(mListCtrl.getSelectItemIndex());
		mPlayerController->Play(mMusicDataController.GetMusicList(pl.name).GetMedia(mMusicListCtrl.getSelectItemIndex()));
		if (mPlayListName != mDisplayListName)
		{
			mPlayListName = mDisplayListName;
		}
	}

	void MainForm::PlayerCallback(void* instance, PlayerStateMessage mes, void *client, WPARAM, LPARAM)
	{
		if (mes == PlayerStateMessage::Stop)
		{
			// one song play end
			// play next
		}
		else if (mes == PlayerStateMessage::UserStop)
		{
			//
		}
	}

	void MainForm::Init()
	{
		UpdatePlayList();
		// set selected playlist and load musiclist
		UpdatePlayListMusic(mConfigController.GetLastSelectedPlayList());
	}

	void MainForm::UpdatePlayList()
	{
		char buf[1024];
		// don't add top 3 playlist
		for (size_t i = 0; i < mMusicDataController.PlayListCount(); i++)
		{
			const struct PlayListModel pld = mMusicDataController.GetPlayListData(i);
			sprintf(buf, PLAY_LIST_TEMPLATE, pld.name.c_str(), mMusicDataController.GetMusicList(pld.name).MusicCount());
			mListCtrl.AddItemWithHtml(buf);
		}
		
	}
	void MainForm::UpdatePlayListMusic(const string& name)
	{
		char buf[2048];
		const MusicListModel& musicList = mMusicDataController.GetMusicList(name);
		mMusicListCtrl.Clear();
		for (size_t i = 0; i < musicList.MusicCount(); i++)
		{
			const MediaModel& m = musicList.GetMedia(i);
			sprintf(buf, MUSIC_LIST_TEMPLATE,"", m.title.c_str(), m.alblum.c_str());
			mMusicListCtrl.AddItemWithHtml(buf);
		}
	}
}