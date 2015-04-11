#pragma once
#include "Core.h"
#include "PlayerEvent.h"
#include "ZWaveInfo.h"
#include "ZPlayerState.h"

using namespace audio;
using namespace audio::player;
using namespace System;
using namespace System::Runtime::InteropServices;

namespace CoreBridge 
{

#pragma managed

	
	public ref class UAudioPlayer
	{
	public:
		UAudioPlayer();
		void close();
		void open(String^ file);
		int play();
		int play(float start, float end);
		int pause();
		int resume();
		int stop();
		int seek(float duration);
		float getPlayDuration();
		float getCurrentPlayStart();
		int setVolumn(int vol);
		int setMute(bool mute);
		ZWaveInfo^ GetWaveInfo();
		ZPlayerState^ GetPlayerState();

	private:
		static void playerCallback(void* instance, PlayerStateMessage mes, void *client, WPARAM w, LPARAM l);
	private:
		AudioPlayer* mPlayer;
		InvokePlayerCallback^ fp;
		GCHandle gch;
		gcroot<UAudioPlayer^>* pointer;
	public:
		event onPlay^ OnPlay;
		event onPause^ OnPause;
		event onStop^ OnStop;
		event onUserStop^ OnUserStop;
		event onResume^ OnResume;
		event onFileOpen^ OnFileOpen;
		event onMute^ OnMute;
		event onVolume^ OnVolume;
		event onSeek^ OnSeek;
	};
}
