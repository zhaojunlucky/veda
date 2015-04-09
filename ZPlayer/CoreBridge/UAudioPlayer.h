#pragma once
#include <AudioPlayer.h>
using namespace audio;
using namespace audio::player;

public ref class UAudioPlayer
{
public:
	UAudioPlayer();
private:
	AudioPlayer* mPlayer;
};

