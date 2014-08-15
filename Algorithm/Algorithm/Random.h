#pragma once
#include <cstdlib>
#include <time.h>
namespace veda
{
	class Random
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


