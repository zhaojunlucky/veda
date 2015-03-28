#include "Fibonacci.h"

namespace al
{
	Fibonacci::Fibonacci()
	{
	}


	Fibonacci::~Fibonacci()
	{
	}

	int Fibonacci::fibonacci(int num)
	{
		return _fibonacci(num);
	}

	int Fibonacci::_fibonacci(int num)
	{
		auto it = mCache.find(num);
		if (it != mCache.end())
		{
			return it->second;
		}

		if (num < 1) { return 0; }
		else if (num == 1){ return 1; }
		else
		{
			auto t = _fibonacci(num - 1) + _fibonacci(num - 2);
			mCache[num] = t;
			return t;
		}
	}
}