#pragma once
#include <math.h>
namespace veda
{
	size_t parent(size_t s, size_t i)
	{
		return floor((i - s - 1) / 2);
	}

	size_t left(size_t s, size_t i)
	{
		return (i - s) * 2 + s + 1;
	}

	size_t right(size_t s, size_t i)
	{
		return (i - s) * 2 + s + 2;
	}

	template <class T, class _Pred>
	void buildHead(T& arr, size_t s )
	{

	}
}