#pragma once
#include <math.h>
namespace veda
{
	size_t parent(size_t s, size_t i)
	{
		return (size_t)floor((i - s - 1) / 2);
	}

	size_t left(size_t s, size_t i)
	{
		return (i != s ? (i - s) : 0) * 2 + s + 1;
	}

	size_t right(size_t s, size_t i)
	{
		return (i != s ? (i - s) : 0) * 2 + s + 2;
	}

	template <class T, class _Pred>
	/*
	  for ascending order, _pred should be std::less, and the heap should be big root heap, this is the default setting
	  for descending order, it should be small root heap
	 */
	void heapAdjust(T& arr, size_t s, size_t length, size_t i, _Pred _pred)
	{
		auto l = left(s, i);
		auto r = right(s, i);
		auto max = i;

		if (l < length && _pred(arr[i] , arr[l]))
		{
			max = l;
		}

		if (r < length && _pred(arr[max], arr[r]))
		{
			max = r;
		}

		if (max != i)
		{
			std::swap(arr[i], arr[max]);
			heapAdjust(arr, s, length, max, _pred);
		}
	}

	template <class T, class _Pred>
	void buildHeap(T& arr, size_t s, size_t length, _Pred _pred)
	{
		if (length >= 2)
		{
			auto i = length / 2 - 1;
			do
			{
				heapAdjust(arr, s, length, i, _pred);
			} while (i-- != 0);
		}
	}
}