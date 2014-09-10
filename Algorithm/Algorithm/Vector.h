#pragma once
#include <iterator>
#include "common.h"
namespace veda
{

	template<class _ZVector>
	class VectorConstIterator :
		public std::iterator < std::random_access_iterator_tag,
		typename _ZVector::value_type,
		typename _ZVector::difference_type,
		typename _ZVector::const_pointer,
		typename _ZVector::const_reference >
	{
	public:
		typedef VectorConstIterator<_ZVector> _ZVectorConstIter;
		typedef typename _ZVector::value_type value_type;
		typedef typename _ZVector::difference_type difference_type;
		typedef typename _ZVector::const_pointer const_pointer;
		typedef typename _ZVector::pointer pointer;
		typedef typename _ZVector::size_type size_type;

		VectorConstIterator()
			:ptr(nullptr), index(0)
		{

		}

		VectorConstIterator(const_pointer ptr, size_type index)
			:ptr(ptr), index(index)
		{

		}

		reference operator*() const
		{
			if (nullptr == ptr)
			{
				throw "vector iterator not incrementable";
			}
			if (index >= ptr->getLength())
			{
				throw "index out of range";
			}
			return (*ptr)[index];
		}

		pointer operator->() const
		{
			// return pointer to class object
			return (_STD pointer_traits<pointer>::pointer_to(**this));
		}

		_ZVectorConstIter& operator++()
		{
			if (nullptr == ptr || index >= ptr->getLength())
			{
				throw "vector iterator not incrementable";
			}
			++index;
			return *this;
		}

		_ZVectorConstIter& operator++(int)
		{
			_ZVectorConstIter tmp = *this;
			++*this;
			return tmp;
		}

		_ZVectorConstIter& operator--()
		{
			if (nullptr == ptr || index >= ptr->getLength())
			{
				throw "vector iterator not incrementable";
			}
			--index;
			return *this;
		}

		_ZVectorConstIter& operator--(int)
		{
			_ZVectorConstIter tmp = *this;
			--*this;
			return tmp;
		}

		_ZVectorConstIter& operator+=(difference_type _off)
		{
			// increment by integer
			if (index + _off >= ptr->length)
			{
				throw "vector iterator not incrementable";
			}

			index += _off;
			return *this;
		}

		_ZVectorConstIter operator+(difference_type _off) const
		{
			_ZVectorConstIter _Tmp = *this;
			return (_Tmp += _Off);
		}

		_ZVectorConstIter& operator-=(difference_type _off)
		{
			// increment by integer
			if (index + _off >= ptr->length)
			{
				throw "vector iterator not incrementable";
			}

			index -= _off;
			return *this;
		}

		_ZVectorConstIter operator-(difference_type _off) const
		{
			_ZVectorConstIter _Tmp = *this;
			return (_Tmp -= _Off);
		}

		difference_type operator-(const _ZVectorConstIter& _Right) const
		{	// return difference of iterators
			_Compat(_Right);
			return (this->_Ptr - _Right._Ptr);
		}

		reference operator[](difference_type _Off) const
		{	// subscript
			return (*((*)ptr[index + _Off]));
		}

		bool operator==(const _ZVectorConstIter& _Right) const
		{	// test for iterator equality
			_Compat(_Right);
			return (this->ptr == _Right.ptr && index == _Right.index);
		}

		bool operator!=(const _ZVectorConstIter& _Right) const
		{	// test for iterator inequality
			return (!(*this == _Right));
		}

		bool operator<(const _ZVectorConstIter& _Right) const
		{	// test if this < _Right
			_Compat(_Right);
			return (this->index < _Right.index);
		}

		bool operator>(const _ZVectorConstIter& _Right) const
		{	// test if this > _Right
			return (_Right < *this);
		}

		bool operator<=(const _ZVectorConstIter& _Right) const
		{	// test if this <= _Right
			return (!(_Right < *this));
		}

		bool operator>=(const _ZVectorConstIter& _Right) const
		{	// test if this >= _Right
			return (!(*this < _Right));
		}

		void _Compat(const _ZVectorConstIter& _Right) const
		{	// test for compatible iterator pair
			if (_Right.ptr != ptr)
			{	// report error
				throw ("vector iterators incompatible");
			}
		}
	protected:
		template<class T>
		friend  class Vector;
		const_pointer ptr;
		size_type index;
	};

	template<class _ZVector>
	class VectorIterator
		: public VectorConstIterator <_ZVector>
	{
	public:

		typedef VectorIterator<_ZVector> _ZVectorIter;
		typedef VectorConstIterator<_ZVector> _ZIterBase;


		typedef typename _ZVector::value_type value_type;
		typedef typename _ZVector::difference_type difference_type;
		typedef typename _ZVector::pointer pointer;
		typedef typename _ZVector::reference reference;


		VectorIterator()
			:VectorConstIterator < _ZVector >()
		{

		}
		VectorIterator(pointer ptr, size_type index)
			:VectorConstIterator < _ZVector >(ptr, index)
		{
			this->ptr = ptr;
		}

		reference operator*() const
		{
			if (nullptr == ptr)
			{
				throw "vector iterator not incrementable";
			}
			if (index >= ptr->getLength())
			{
				throw "index out of range";
			}
			return (*ptr)[index];
		}

		pointer operator->() const
		{	// return pointer to class object
			return (_STD pointer_traits<pointer>::pointer_to(**this));
		}


		_ZVectorIter& operator++()
		{
			++*(_ZIterBase*)this;
			return *this;
		}

		_ZVectorIter& operator++(int)
		{
			// postincrement
			_ZArrayIter tmp = *this;
			++*this;
			return tmp;
		}

		_ZVectorIter& operator--()
		{
			--*(_ZIterBase)this;
			return *this;
		}
		_ZVectorIter& operator--(int)
		{
			_ZVectorIter tmp = *this;
			--*this;
			return tmp;
		}

		_ZVectorIter& operator+=(difference_type _off)
		{
			// increment by integer
			*(_ZIterBase)this += _off;
			return *this;
		}

		_ZVectorIter operator+(difference_type _Off) const
		{	// return this + integer
			_ZVectorIter _Tmp = *this;
			return (_Tmp += _Off);
		}

		_ZVectorIter& operator-=(difference_type _Off)
		{	// decrement by integer
			return (*this += -_Off);
		}

		_ZVectorIter operator-(difference_type _Off) const
		{	// return this - integer
			_ZVectorIter _Tmp = *this;
			return (_Tmp -= _Off);
		}

		difference_type operator-(const _ZIterBase& _Right) const
		{	// return difference of iterators
			return (*(_ZIterBase*)this - _Right);
		}

		reference operator[](difference_type _Off) const
		{	// subscript
			return (*((*)arr[index + _Off]));
		}
	private:
		pointer ptr;
	};

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
		typedef VectorConstIterator<_ZVector> const_iterator;
		typedef VectorIterator<_ZVector> iterator;

		Vector()
			:size(0)
		{
			capacity = DEFAULT_CAPACITY;
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
				deleteptray<T>(data);
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

		value_type removeAt(size_type index)
		{
			if (index >= size)
			{
				throw "index out of range";
			}
			value_type tmp = data[index];
			for (size_type i = index; i < size - 1; i++)
			{
				data[i] = data[i + 1];
			}
			--size;
			elementRemoved();
			return tmp;
		}

		iterator removeAt(iterator& it)
		{
			removeAt(it.index);
			return iterator(this,it.index);
		}

		const_iterator removeAt(const_iterator& it)
		{
			removeAt(it.index);
			return const_iterator(this, it.index);
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

		const_iterator cbegin() const _NOEXCEPT
		{
			return const_iterator(this, 0);
		}

		const_iterator cend() const _NOEXCEPT
		{
			return const_iterator(this, size);
		}


		iterator begin() _NOEXCEPT
		{
			return iterator(this, 0);
		}

		iterator end() _NOEXCEPT
		{
			return iterator(this, size);
		}
	protected:
		void elementRemoved()
		{
			size_type len = capacity / 4;
			if (len >= size && capacity > 256)
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
		const size_type DEFAULT_CAPACITY = 64;
	};
}