#pragma once
#include <algorithm>
#include "Array.h"

namespace veda
{
	template<class T, class U, class _Pred>
	void merge(T&arr, U& tmp, size_t offset, size_t lo, size_t mid, size_t hi, _Pred _pred)
	{
		// check low, high
		for (size_t i = lo; i <= hi; i++)
		{
			tmp[i - offset] = arr[i];
		}

		size_t i = lo;
		size_t j = mid + 1;

		for (size_t k = lo; k <= hi; k++)
		{
			if (i > mid) 
			{
				arr[k] = tmp[j++ - offset];
			}
			else if (j > hi)
			{
				arr[k] = tmp[i++ - offset];
			}
			else if (_pred(tmp[i - offset], tmp[j - offset]))
			{
				arr[k] = tmp[i++ - offset];
			}
			else
			{
				arr[k] = tmp[j++ - offset];
			}

		}
	}

	template<class T, class U, class _Pred>
	void mergeSort(T&arr, U& tmp, size_t offset, size_t lo, size_t hi, _Pred _pred)
	{
		if (lo >= hi)
		{
			return;
		}
		size_t mid = (lo + hi) / 2;
		mergeSort(arr, tmp, offset, lo, mid, _pred);
		mergeSort(arr, tmp, offset, mid + 1, hi, _pred);
		merge(arr, tmp, offset, lo, mid, hi, _pred);
	}
}