#pragma once
#include <xAudio2.h>
namespace audio
{
	namespace player
	{
#define STREAMING_BUFFER_SIZE 65536
#define MAX_BUFFER_COUNT 3
#define MAX_VOLUME 10000
#define MIN_VOLUME 0
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p)=NULL; } }
#endif
		struct Audio2
		{
			IXAudio2* pXAudio2;
			IXAudio2MasteringVoice* pMasteringVoice;
			IXAudio2SourceVoice* pSourceVoice;
			bool bInitialized;
			// reverb
			IUnknown *pReverbEffect;
			IXAudio2SubmixVoice *pSubmixVoice;
		};

		enum PlayerStateMessage
		{
			Play,
			Pause,
			Stop,
			UserStop,
			Resume,
			Open,
			Mute,
			Unmute,
			Volume,
			Seek
		};

		struct PlayerState
		{
			bool isPlaying;
			bool isPause;
			bool isStop;
			bool isMute;
			int volume;
		};

		struct PlayControl
		{
			float startSec;
			float endSec;
			DWORD start;
			DWORD end;
		};

		enum PlayerError
		{
			InvalidDecoder,
			InvalidPlayTime,
			InvalidPlayerPara,
			FailToCreateSourceVoice
		};
		typedef void(__stdcall * ZACallbackFunction)(void* instance, PlayerStateMessage mes, void *client, WPARAM, LPARAM);
		struct Callback
		{
			void* client;
			ZACallbackFunction callbackFunc;
		};
	}
}