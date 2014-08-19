#pragma once
#include "Array.h"
#include "Vector.h"
#include <algorithm>

namespace veda
{
	template<class T,class _Pred>
	void selection(T& arr, size_t start,size_t length,_Pred _pred)
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
					std::swap(arr[j],arr[j-1]);
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
		return check(arr,s,length,std::less<>());
	}
}
