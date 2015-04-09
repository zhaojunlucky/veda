#pragma once
#include <AudioPlayer.h>
using namespace audio;
using namespace audio::player;

namespace CoreBridge 
{
	public ref class UAudioPlayer
	{
	public:
		UAudioPlayer();
	private:
		AudioPlayer* mPlayer;
	};
}
