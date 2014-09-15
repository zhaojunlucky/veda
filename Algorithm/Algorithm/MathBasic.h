#pragma once
namespace veda
{
	template <class T>
	T maxValue(T& a, T& b)
	{
		return a >= b ? a : b;
	}

	template <class T>
	T minValue(T& a, T& b)
	{
		return a <= b ? a : b;
	}
}