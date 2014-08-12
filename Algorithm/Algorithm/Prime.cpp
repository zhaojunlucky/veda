#include "Prime.h"
#include <cstdlib>
namespace veda
{
	template <class Integer>
	static bool isPrime(Integer number)
	{
		number = std::abs(number);

		if (number == 0 || number == 1)
		{
			return false;
		}

		Integer divisor;
		for (divisor = number / 2; number%divisor != 0; --divisor)
		{

		}

		return divisor == 1;
	}

	bool isPrime(int num)
	{
		return isPrime<int>(num);
	}
	bool isPrime(long num)
	{
		return isPrime<long>(num);
	}

	bool isPrime(__int64 num)
	{
		return isPrime<__int64>(num);
	}
}