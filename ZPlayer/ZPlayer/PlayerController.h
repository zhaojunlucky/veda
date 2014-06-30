#pragma once
#include "PlayListModel.h"
#include "MediaModel.h"
#include "MusicListModel.h"
#include "PlayerControl.h"

namespace zpl
{
	class PlayerController
	{
	public:
		PlayerController();
		~PlayerController();
		void Play();
		void Play(const MediaModel& m);
		void Pause();
		void Resume();
		void SetVolumn(float percentage);
		void Seek(float percentage);
		void Stop();
		AudioPlayer* GetPlayer();
	private:
		PlayerControl mPc;
		AudioPlayer* mPlayer;
	};
}


