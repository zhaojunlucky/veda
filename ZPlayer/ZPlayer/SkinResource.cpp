#include "SkinResource.h"


SkinResource::SkinResource()
{
	loadResource();
}


SkinResource::~SkinResource()
{
}

void SkinResource::loadResource()
{
	String dir = L"ui\\images\\play_control\\";

	ShuffleNormal = dir + L"shuffle_normal.png";
	ShuffleDown = dir + L"shuffle_down.png";

	RepeatAllNormal = dir + L"repeat_normal.png";
	RepeatAllDown = dir + L"repeat_down.png";

	PlayNormal = dir + L"play_normal.png";
	PlayDown = dir + L"play_down.png";

	PauseNormal = dir + L"pause_normal.png";
	PauseDown = dir + L"pause_down.png";

	SoundMuteNormal = dir + L"sound_mute_normal.png";
	SoundMuteDown = dir + L"sound_mute_down.png";

	SoundMinNormal = dir + L"sound_min_normal.png";
	SoundMinDown = dir + L"sound_min_down.png";

	SoundLowNormal = dir + L"sound_low_normal.png";
	SoundLowDown = dir + L"sound_low_down.png";


	SoundMiddleNormal = dir + L"sound_middle_normal.png";
	SoundMiddleDown = dir + L"sound_middle_down.png";

	SoundMaxNormal = dir + L"sound_max_normal.png";
	SoundMaxDown = dir + L"sound_max_down.png";
}