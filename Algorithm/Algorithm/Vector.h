#pragma once
namespace veda
{
	template<class T>
	class Vector
	{
	public:
		typedef Vector<T> _ZVector;

		typedef typename T value_type;
		typedef typename int difference_type;
		typedef typename const  _ZVector* const_pointer;
		typedef typename T& reference;
		typedef typename const T& const_reference;
		typedef typename _ZVector * pointer;
		typedef typename size_t size_type;

		Vector()
			:capacity(DEFAULT_CAPACITY), size(0)
		{

		}

		Vector(size_type capacity)
			:capacity(capacity), size(0)
		{

		}

		Vector(const _ZVector& other)
		{
			
		}

		virtual ~Vector()
		{

		}

		_ZVector& operator=(const _ZVector& other)
		{
			return *this;
		}

		void resize(size_type size)
		{

		}

		void reserve(size_type size)
		{

		}

		size_type getCapacity() const
		{
			return capacity;
		}

		size_type getLength() const
		{
			return size;
		}

		void add(value_type& v)
		{

		}

		void add(value_type&& v)
		{

		}

		void clear()
		{

		}

		
	protected:
		size_type capacity;
		size_type size;
		value_type* data;
		const size_type DEFAULT_CAPACITY = 10;
	};
}