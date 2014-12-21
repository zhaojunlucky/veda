#pragma once
#include <cstdlib>
#include <time.h>
#include "Algorithm.h"
namespace veda
{
	class AL_EXPORT Random
	{
	public:
		Random();
		~Random();

		int getRandomMaxInt() const;
		int getRandomMinInt() const;
		int randomInt() const;
		int randomInt(int min, int max) const;
	};
}


