#pragma once
#include "Array.h"

template <class T>
int binarySearch(const veda::Array<T>& arr, const T& v);

template <class T>
int binarySearch(const veda::Array<T>& arr, const T& v)
{
	long l = 0;
	long h = arr.length() - 1;
	long m;
	while (l <= h)
	{
		m = l + (h - l) / 2;
		if (v > arr[m])
		{
			l = m + 1;
		}
		else if (v < arr[m])
		{
			h = m - 1;
		}
		else
		{
			return (int)m;
		}
	}
	return -1;
}