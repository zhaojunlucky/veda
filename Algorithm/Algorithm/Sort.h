#pragma once
#include "Array.h"
#include "Vector.h"
#include <algorithm>
namespace veda
{
	
	template<class T>
	void insertionSort(Array<T>& arr)
	{
		insertionSort(arr, std::less<>());
	}

	template<class T, class _Pred>
	void insertionSort(Array<T>& arr, _Pred _pred)
	{

	}
}
