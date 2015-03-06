#pragma once
namespace veda
{
	template<class T>
	void deleteArray(T* ptr)
	{
		if (nullptr != ptr)
		{
			delete[]ptr;
		}
	}
	template<class T>
	void deletePtr(T* ptr)
	{
		if (nullptr != ptr)
		{
			delete ptr;
		}
	}

	template<class T>
	void exchange(T& a, T& b)
	{
		T& c = a;
		a = b;
		b = c;
	}
}


