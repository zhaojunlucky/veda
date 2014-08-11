#pragma once
#include "common.h"
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
			alloc(capacity);
		}

		Vector(size_type capacity)
			:capacity(capacity), size(0)
		{
			alloc(capacity);
		}

		Vector(const _ZVector& other)
			:capacity(other.capacity), size(other.size)
		{
			alloc(capacity);
			copy(other.data);
		}

		virtual ~Vector()
		{
			deleteArray(data);
		}

		_ZVector& operator=(const _ZVector& other)
		{
			if (this != &other)
			{
				deleteArray<T>(data);
				capacity = other.capacity;
				size = other.size;
				copy(other.data);
			}
			return *this;
		}

		void resize(size_type size)
		{
			if (size >= capacity)
			{
				capacity = size;
				reallocAndCopy(capacity);	
			}
			this->size = size;
		}

		void reserve(size_type capacity)
		{
			if (capacity > this->capacity)
			{
				this->capacity = capacity;
				reallocAndCopy(capacity);
			}
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
			checkCapacity();
			data[size++] = v;
		}

		void add(value_type&& v)
		{
			checkCapacity();
			data[size++] = v;
		}

		void clear()
		{
			size = 0;
		}

		void shrink2Fit()
		{
			if (capacity != size)
			{
				this->capacity = size > 0 ? size : DEFAULT_CAPACITY;
				reallocAndCopy(capacity);
			}
		}

		void removeAt(size_type index)
		{
			if (index >= size)
			{
				throw "index out of range";
			}
			for (size_type i = index; i < size - 1; i++)
			{
				data[i] = data[i + 1];
			}
			size--;
			elementRemoved();
		}

		void removeAt(/*iterator*/)
		{
			elementRemoved(); 
		}

		reference operator[](size_type index)
		{
			return data[index];
		}

		reference at(size_type index)
		{
			return data[index];
		}

		const_reference operator[](size_type index) const
		{
			return data[index];
		}

		const_reference at(size_type index) const
		{
			return data[index];
		}
	protected:
		void elementRemoved()
		{
			size_type len = capacity / 4;
			if (len >= size)
			{
				capacity = len;
				reallocAndCopy(capacity);
			}
		}

		void checkCapacity()
		{
			if (size >= capacity)
			{
				capacity *= 2;
				reallocAndCopy(capacity);
			}
		}

		void alloc(size_type len)
		{
			data = new value_type[len];
		}

		void copy(const value_type* other)
		{
			for (size_type i = 0; i < size; i++)
			{
				data[i] = other[i];
			}
		}

		void reallocAndCopy(size_type newCapacity)
		{
			value_type* old = data;
			alloc(newCapacity);
			copy(old);
			deleteArray(old);
		}

	protected:
		size_type capacity;
		size_type size;
		value_type* data;
		const size_type DEFAULT_CAPACITY = 10;
	};
}