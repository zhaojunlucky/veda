#pragma once
#include "Core.h"
#include "PlayerEvent.h"
#include "ZWaveInfo.h"
#include "ZPlayerState.h"
#include "Decoder.h"

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
		// the volumn range is [0,10000]
		int setVolumn(int vol);
		int setMute(bool mute);
		ZWaveInfo^ getWaveInfo();
		ZPlayerState^ getPlayerState();

	private:
		static void playerCallback(void* instance, PlayerStateMessage mes, void *client, WPARAM w, LPARAM l);
	private:
		AudioPlayer* mPlayer;
		Decoder* mDecoder;
		InvokePlayerCallback^ fp;
		GCHandle gch;
		gcroot<UAudioPlayer^>* pointer;

	public:
		onPlay^ OnPlay;
		onPause^ OnPause;
		onStop^ OnStop;
		onUserStop^ OnUserStop;
		onResume^ OnResume;
		onFileOpen^ OnFileOpen;
		onMute^ OnMute;
		onVolume^ OnVolume;
		onSeek^ OnSeek;
	};
}
