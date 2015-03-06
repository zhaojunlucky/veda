#pragma once
#include "Array.h"
#include "Vector.h"
#include <algorithm>
#include "Random.h"
#include "MergeSort.h"
#include "HeapSort.h"

namespace veda
{
	template<class T, class _Pred>
	void selection(T& arr, size_t start, size_t length, _Pred _pred)
	{
		size_t endIndex = start + length;
		size_t guard;
		for (size_t i = start; i < endIndex; i++)
		{
			guard = i;
			for (size_t j = i; j < endIndex; j++)
			{
				if (_pred(arr[j], arr[guard]))
				{
					guard = j;
				}
			}
			// swap 
			if (guard != i)
			{
				std::swap(arr[guard], arr[i]);
			}
		}
	}

	template<class T>
	void selection(T& arr, size_t start, size_t length)
	{
		selection(arr, start, length, std::less<>());
	}

	template<class T, class _Pred>
	void insertion(T& arr, size_t s, size_t length, _Pred _pred)
	{
		size_t endIndex = s + length;

		for (size_t i = s + 1; i < endIndex; i++)
		{

			for (size_t j = i; j >= s + 1; j--)
			{
				if (_pred(arr[j], arr[j - 1]))
				{
					std::swap(arr[j], arr[j - 1]);
				}
			}
		}
	}

	template<class T>
	void insertion(T& arr, size_t s, size_t length)
	{
		insertion(arr, s, length, std::less<>());
	}

	template <class T, class _Pred>
	void shell(T& arr, size_t s, size_t length, _Pred _pred)
	{
		size_t h = 1;
		while (3 * h < length)
		{
			h = 3 * h + 1;
		}

		while (h >= 1)
		{
			for (size_t i = h; i < length + s; i++)
			{
				for (size_t j = i; j >= h && _pred(arr[j], arr[j - h]); j -= h)
				{
					std::swap(arr[j], arr[j - h]);
				}
			}
			h /= 3;
		}
	}
	
	template <class T>
	void shell(T& arr, size_t s, size_t length)
	{
		shell(arr, s, length, std::less<>());
	}

	template < class T, class _Pred>
	void mergeSort(T& arr, size_t s, size_t length, _Pred _pred)
	{
		auto a = arr[s];
		Array<decltype(a)> tmp(length);
		mergeSort(arr, tmp, s, s, length + s - 1, _pred);
	}

	template < class T>
	void mergeSort(T& arr, size_t s, size_t length)
	{
		mergeSort(arr, s, length, std::less<>());
	}

	template <class T>
	void shuffle(T& arr, size_t length)
	{
		Random random;
		size_t r;
		for (auto i = 0; i < length; i++)
		{
			r = random.randomInt(0, i + 1);
			std::swap(arr[i], arr[r]);
		}
	}

	template <class T, class _Pred>
	void heapSort(T& arr, size_t s, size_t length, _Pred _pred)
	{
		buildHeap(arr, s, length, _pred);
		for (auto i = length - 1; i >= 1; i--)
		{
			std::swap(arr[i], arr[s]);
			heapAdjust(arr, s, length, i, _pred);
		}
	}

	template <class T>
	void heapSort(T& arr, size_t s, size_t length)
	{
		heapSort(arr, s, length, std::less<>());
	}

	
	template <class T, class _Pred>
	/*
	  sort 5 numbers within 7 times comparation
	  arr the array to be sorted
	  s the start index
	 */
	void sort5(T& arr, size_t s, _Pred _pred)
	{
		size_t a = s;
		size_t b = s + 1;
		size_t c = s + 2;
		size_t d = s + 3;
		size_t e = s + 4;

		
		
	}

	template <class T>
	/*
	 sort 5 numbers within 7 times comparation
	 s start index
	*/
	void sort5(T& arr, size_t s)
	{
		sort5(arr, s, std::less<>());
	}

	template <class T, class _Pred>
	bool check(const T&arr, size_t s, size_t length, _Pred _pred)
	{
		bool ret = true;
		for (size_t i = s; i < s + length - 1; i++)
		{
			if (!_pred(arr[i], arr[i + 1]))
			{
				ret = false;
				break;
			}
		}
		return ret;
	}

	template<class T>
	bool check(const T&arr, size_t s, size_t length)
	{
		return check(arr, s, length, std::less<>());
	}
}
