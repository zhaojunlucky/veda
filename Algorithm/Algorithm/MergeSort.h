#pragma once
#include <algorithm>
#include "Array.h"

namespace veda
{

	template<class T, class U, class _Pred>
	void mergeSort(T&arr, U& tmp, size_t s, size_t length, _Pred _pred)
	{

	}


	template < class T, class _Pred>
	void mergeSort(T& arr, size_t s, size_t length, _Pred _pred)
	{
		auto a = arr[s];
		Array<decltype(a)> tmp(length);
		mergeSort(arr, tmp, s, length, _pred);
	}

	template < class T>
	void mergeSort(T& arr, size_t s, size_t length)
	{
		mergeSort(arr, s, length, std::less<>());
	}
}