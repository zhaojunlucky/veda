#pragma once
namespace al
{
	template <class T>
	class Iterator
	{
	public:
		Iterator(){}
		virtual ~Iterator(){}
		virtual bool hasNext() = 0;
		virtual T get() = 0;
	};

	template <class T>
	class NullIterator : public Iterator<T>
	{
	public:
		NullIterator(){}
		virtual ~NullIterator(){}

		virtual bool hasNext()
		{
			return false;
		}

		virtual T get()
		{
			// should not be called
		}
	};
}


