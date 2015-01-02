#pragma once
#include <hash_map>
#include <functional>
#include "veda.h"
namespace veda
{
	template<class E>
	class Event
	{
	public:
		VEDA_EXPORT Event(){}
		VEDA_EXPORT virtual ~Event(){}

		Event& operator += (const std::function<T>& other)
		{

			return *this;
		}
	private:


	};
}