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
		typedef std::function<E>
		VEDA_EXPORT Event(){}
		VEDA_EXPORT virtual ~Event(){}

		Event& operator += (const std::function<E>& other)
		{

			return *this;
		}
	private:
		std::hash_map<>

		 
	};
}