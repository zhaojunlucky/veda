#include "stdafx.h"
#include "UAudioPlayer.h"
#include "DecoderFactory.hpp"

namespace CoreBridge
{
	void UAudioPlayer::playerCallback(void* instance, PlayerStateMessage mes, void *client, WPARAM w, LPARAM l)
	{
		gcroot<UAudioPlayer^>* p = (gcroot<UAudioPlayer^>*)client;
		//(*p)->
		switch (mes)
		{
		case PlayerStateMessage::Mute: if ((*p)->OnMute != nullptr) (*p)->OnMute(true); break;
		case PlayerStateMessage::Open: if ((*p)->OnFileOpen != nullptr) (*p)->OnFileOpen(); break;
		case PlayerStateMessage::Pause: if ((*p)->OnPause != nullptr) (*p)->OnPause(); break;
		case PlayerStateMessage::Play: if ((*p)->OnPlay != nullptr) (*p)->OnPlay(); break;
		case PlayerStateMessage::Resume: if ((*p)->OnResume != nullptr) (*p)->OnResume(); break;
		case PlayerStateMessage::Seek: if ((*p)->OnSeek != nullptr) (*p)->OnSeek(); break;
		case PlayerStateMessage::Stop: if ((*p)->OnStop != nullptr) (*p)->OnStop(); break;
		case PlayerStateMessage::Unmute: if ((*p)->OnMute != nullptr) (*p)->OnMute(false); break;
		case PlayerStateMessage::UserStop: if ((*p)->OnUserStop != nullptr) (*p)->OnUserStop(); break;
		case PlayerStateMessage::Volume: if ((*p)->OnVolume != nullptr) (*p)->OnVolume(); break;
		default:break;
		};
	}
	UAudioPlayer::UAudioPlayer()
	{
		mPlayer = new AudioPlayer;
		mDecoder = NULL;
		fp = gcnew InvokePlayerCallback(playerCallback);
		gch = GCHandle::Alloc(fp);
		IntPtr ip = Marshal::GetFunctionPointerForDelegate(fp);
		ZACallbackFunction cb = static_cast<ZACallbackFunction>(ip.ToPointer());
		pointer = new gcroot<UAudioPlayer^>(this);
		mPlayer->SetCallback(cb, (void*)pointer);
	}

	void UAudioPlayer::close()
	{
		if (mPlayer)
		{
			mPlayer->Stop();
			delete mPlayer;
			mPlayer = NULL;
		}
		
		gch.Free();
		delete pointer;
	}

	void UAudioPlayer::open(String^ file)
	{
		mPlayer->Stop();
		if (mDecoder)
		{
			mDecoder->Close();
			delete mDecoder;
			mDecoder = NULL;
		}
		pin_ptr<const wchar_t> wch = PtrToStringChars(file);
		mDecoder = DecoderFactory::CreateDecoderByFile(wch);
		if (mDecoder == NULL)
		{
			throw gcnew Exception("Unsupport media type.");
		}
		if (0 != mDecoder->Open(wch))
		{
			throw gcnew Exception("Fail to open media type.");
		}
		mPlayer->Open(mDecoder);

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
	ZWaveInfo^ UAudioPlayer::getWaveInfo()
	{
		auto w = mPlayer->GetWaveInfo();
		auto zwi = gcnew ZWaveInfo();
		zwi->bitrate = w.bitrate;
		zwi->cbSize = w.waveFormatex.cbSize;
		zwi->durationTime = w.durationTime;
		zwi->nAvgBytesPerSec = w.waveFormatex.nAvgBytesPerSec;
		zwi->nBlockAlign = w.waveFormatex.nBlockAlign;
		zwi->nChannels = w.waveFormatex.nChannels;
		zwi->nSamplesPerSec = w.waveFormatex.nSamplesPerSec;
		zwi->waveSize = w.waveSize;
		zwi->wBitsPerSample = w.waveFormatex.wBitsPerSample;
		zwi->wFormatTag = w.waveFormatex.wFormatTag;
		return zwi;
	}
	ZPlayerState^ UAudioPlayer::getPlayerState()
	{
		auto p = mPlayer->GetPlayerState();
		auto zps = gcnew ZPlayerState();
		zps->isMute = p.isMute;
		zps->isPause = p.isPause;
		zps->isPlaying = p.isPlaying;
		zps->isStop = p.isStop;
		zps->volume = p.volume;
		return zps;
	}
}
