#pragma once
namespace veda
{
	template <class T>
	T maxValue(T a, T b)
	{
		return a >= b ? a : b;
	}
}