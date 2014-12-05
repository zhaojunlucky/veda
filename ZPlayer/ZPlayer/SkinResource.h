#pragma once
#include <ZString.h>
using namespace veda;
#include <memory>


class SkinResource
{
public:
	SkinResource();
	~SkinResource();
	void loadResource();
public:
	StringPtr ShuffleNormal;
	StringPtr ShuffleDown;
	StringPtr RepeatAllNormal;
	StringPtr RepeatAllDown;
	StringPtr PlayNormal;
	StringPtr PlayDown;
	StringPtr PauseNormal;
	StringPtr PauseDown;
	StringPtr SoundMuteNormal;
	StringPtr SoundMuteDown;
	StringPtr SoundMinNormal;
	StringPtr SoundMinDown;
	StringPtr SoundLowNormal;
	StringPtr SoundLowDown;
	StringPtr SoundMiddleNormal;
	StringPtr SoundMiddleDown;
	StringPtr SoundMaxNormal;
	StringPtr SoundMaxDown;


};

