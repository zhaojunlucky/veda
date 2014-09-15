#include "Random.h"

namespace veda
{
	Random::Random()
	{
		srand((unsigned int)time(NULL));
	}


	Random::~Random()
	{
	}

	int Random::getRandomMaxInt() const
	{
		return RAND_MAX;
	}

	int Random::getRandomMinInt() const
	{
		return 0;
	}

	int Random::randomInt() const
	{
		return rand();
	}

	int Random::randomInt(int min, int max) const
	{
		return randomInt() % max + min;
	}
}