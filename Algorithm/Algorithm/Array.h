#pragma once
#include <assert.h>
#include "common.h"

template <class T>
class Array
{
public:
	Array(size_t len)
		:size(len)
	{
		assert(len > 0);
		alloc(len);
	}
	Array(const Array& arr)
	{
		size = arr.size;
		copy(arr.data);
	}
	~Array()
	{
		deleteArray<T>(data);
	}
	size_t length() const
	{
		return size;
	}
	Array& operator=(const Array& arr)
	{
		if (this != &arr)
		{
			deleteArray<T>(data);
			size = arr.size;
			copy(arr.data);
		}
		return *this;
	}
	T& operator[](size_t index)
	{
		return data[index];
	}
	const T& operator[](size_t index) const
	{
		return data[index];
	}

private:
	void alloc(size_t size)
	{
		data = new T[size];
	}
	void copy(const T* src)
	{
		for (size_t i = 0; i < size; i++)
		{
			data[i] = src[i];
		}
	}
private:
	size_t size;
	T* data;
};

