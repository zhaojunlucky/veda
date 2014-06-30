#include "PlayerController.h"

namespace zpl
{
	PlayerController::PlayerController()
	{
		mPc.InitPlayer();
		mPlayer = mPc.player.get();
	}


	PlayerController::~PlayerController()
	{
	}
	void PlayerController::Play()
	{
		mPlayer->Play();
	}
	void PlayerController::Play(const MediaModel& m)
	{
		mPc.PreparePlay(m);
		m.isCue ? mPlayer->Play(m.cueInfo.start, m.cueInfo.end) : mPlayer->Play();
	}
	void PlayerController::Stop()
	{
		mPlayer->Stop();
	}
	void PlayerController::Pause()
	{
		mPlayer->Pause();
	}
	void PlayerController::Resume()
	{
		mPlayer->Resume();
	}

	void PlayerController::SetVolumn(float percentage)
	{
		mPlayer->SetVolumne(MAX_VOLUME*percentage);
	}
	void PlayerController::Seek(float percentage)
	{
		mPlayer->Seek(mPlayer->GetWaveInfo().durationTime*percentage);
	}

	AudioPlayer* PlayerController::GetPlayer()
	{
		return mPlayer;
	}
}