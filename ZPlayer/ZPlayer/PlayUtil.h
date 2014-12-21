#pragma once
#include <ZString.h>
using namespace veda;
class PlayUtil
{
public:
	PlayUtil();
	~PlayUtil();
	static StringPtr formatTime(float duration);
	static size_t getRandomNext(size_t total);
};

