#include "stdafx.h"
#include "UAudioPlayer.h"

namespace CoreBridge
{
	void UAudioPlayer::playerCallback(void* instance, PlayerStateMessage mes, void *client, WPARAM w, LPARAM l)
	{
		gcroot<UAudioPlayer^>* p = (gcroot<UAudioPlayer^>*)instance;
		//(*p)->
		switch (mes)
		{
		//case PlayerStateMessage::Mute: (*p)->OnMute(true); break;
		//case PlayerStateMessage::Open: (*p)->OnFileOpen(); break;
		//case PlayerStateMessage::Pause: (*p)->OnPause(); break;
		//case PlayerStateMessage::Play: (*p)->OnPlay(); break;
		//case PlayerStateMessage::Resume: (*p)->OnResume(); break;
		//case PlayerStateMessage::Seek: (*p)->OnSeek(); break;
		case PlayerStateMessage::Stop: (*p)->OnStop(); break;
		//case PlayerStateMessage::Unmute: (*p)->OnMute(false); break;
		case PlayerStateMessage::UserStop: (*p)->OnUserStop(); break;
		//case PlayerStateMessage::Volume: (*p)->OnVolume(); break;
		default:break;
		};
	}
	UAudioPlayer::UAudioPlayer()
	{
		mPlayer = new AudioPlayer;
		fp = gcnew InvokePlayerCallback(playerCallback);
		gch = GCHandle::Alloc(fp);
		IntPtr ip = Marshal::GetFunctionPointerForDelegate(fp);
		ZACallbackFunction cb = static_cast<ZACallbackFunction>(ip.ToPointer());
		pointer = new gcroot<UAudioPlayer^>(this);
		mPlayer->SetCallback(cb, (void*)pointer);
	}

	void UAudioPlayer::close()
	{
		gch.Free();
		delete pointer;
	}

	void UAudioPlayer::open(String^ file)
	{
		
	}
	int UAudioPlayer::play()
	{
		return mPlayer->Play();
	}
	int UAudioPlayer::play(float start, float end)
	{
		return mPlayer->Play(start, end);
	}
	int UAudioPlayer::pause()
	{
		return mPlayer->Pause();
	}
	int UAudioPlayer::resume()
	{
		return mPlayer->Resume();
	}
	int UAudioPlayer::stop()
	{
		return mPlayer->Stop();
	}
	int UAudioPlayer::seek(float duration)
	{
		return mPlayer->Seek(duration);
	}
	float UAudioPlayer::getPlayDuration()
	{
		return mPlayer->GetPlayDuration();
	}
	float UAudioPlayer::getCurrentPlayStart()
	{
		return mPlayer->getCurrentPlayStart();
	}
	int UAudioPlayer::setVolumn(int vol)
	{
		return mPlayer->SetVolumne(vol);
	}
	int UAudioPlayer::setMute(bool mute)
	{
		return mPlayer->SetMute(mute);
	}
	ZWaveInfo^ UAudioPlayer::GetWaveInfo()
	{
		return gcnew ZWaveInfo();
	}
	ZPlayerState^ UAudioPlayer::GetPlayerState()
	{
		return gcnew ZPlayerState();
	}
}
