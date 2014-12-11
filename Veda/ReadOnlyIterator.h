#pragma once
#include "veda.h"
namespace veda
{
	template <class T>
	class VEDA_EXPORT Iterator
	{
	public:
		virtual bool hasNext() = 0;
		virtual const T& get() = 0;
	};

	template <class T>
	class VEDA_EXPORT NullIterator : public Iterator<T>
	{
	public:
		NullIterator(){}
		virtual ~NullIterator(){}

		virtual bool hasNext() const
		{
			return false;
		}

		virtual const T& get()
		{
			// should not be called
		}
	};
}