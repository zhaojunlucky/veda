#include "PlayUtil.h"
#include <memory>
#include <Random.h>

PlayUtil::PlayUtil()
{
}


PlayUtil::~PlayUtil()
{
}

StringPtr PlayUtil::formatTime(float duration)
{
	String* s = new String;
	int min = duration / 60;
	s->format(L"%02d:%02d", min, (int)(duration - min * 60));
	return std::shared_ptr<String>(s);
}

size_t PlayUtil::getRandomNext(size_t total)
{
	Random rand;
	return rand.randomInt(0, total - 1);
}