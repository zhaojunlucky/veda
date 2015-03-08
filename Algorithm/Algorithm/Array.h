#pragma once
#include <iterator>
#include <assert.h>
#include "ALCommon.h"

namespace veda
{
	template<class _ZArray>
	class ArrayConstIterator
		: public std::iterator < std::random_access_iterator_tag,
		typename _ZArray::value_type,
		typename _ZArray::difference_type,
		typename _ZArray::const_pointer,
		typename _ZArray::const_reference >
	{
	public:
		typedef ArrayConstIterator<_ZArray> _ZArrayConstIter;
		//typedef random_access_iterator_tag iterator_category;

		typedef typename _ZArray::value_type value_type;
		typedef typename _ZArray::difference_type difference_type;
		typedef typename _ZArray::const_pointer const_pointer;
		typedef typename _ZArray::const_reference reference;
		typedef typename _ZArray::pointer pointer;
		typedef typename _ZArray::size_type size_type;

		ArrayConstIterator()
			:index(0), arr(nullptr)
		{

		}
		ArrayConstIterator(size_type index, const_pointer arr)
			:index(index), arr(arr)
		{

		}

		reference operator*() const
		{
			if (nullptr == arr)
			{
				throw "array iterator not incrementable";
			}
			if (index >= arr->length())
			{
				throw "index out of range";
			}

			return (*arr)[index];
		}

		pointer operator->() const
		{	// return pointer to class object
			return (_STD pointer_traits<pointer>::pointer_to(**this));
		}


		_ZArrayConstIter& operator++()
		{
			if (nullptr == arr || index >= arr->length())
			{
				throw "array iterator not incrementable";
			}
			++index;
			return *this;
		}

		_ZArrayConstIter& operator++(int)
		{
			// postincrement
			_ZArrayIter tmp = *this;
			++*this;
			return tmp;
		}

		_ZArrayConstIter& operator--()
		{
			if (nullptr == arr || index == 0)
			{
				throw "array iterator not incrementable";
			}
			--index;
			return *this;
		}
		_ZArrayConstIter& operator--(int)
		{
			_ZArrayIter tmp = *this;
			--*this;
			return tmp;
		}

		_ZArrayConstIter& operator+=(difference_type _off)
		{
			// increment by integer
			if (index + _off >= arr->length)
			{
				throw "array iterator not incrementable";
			}

			index += _off;
			return *this;
		}

		_ZArrayConstIter operator+(difference_type _Off) const
		{	// return this + integer
			_ZArrayIter _Tmp = *this;
			return (_Tmp += _Off);
		}

		_ZArrayConstIter& operator-=(difference_type _Off)
		{	// decrement by integer
			return (*this += -_Off);
		}

		_ZArrayConstIter operator-(difference_type _Off) const
		{	// return this - integer
			_ZArrayIter _Tmp = *this;
			return (_Tmp -= _Off);
		}

		difference_type operator-(const _ZArrayConstIter& _Right) const
		{	// return difference of iterators
			_Compat(_Right);
			return (this->_Ptr - _Right._Ptr);
		}

		reference operator[](difference_type _Off) const
		{	// subscript
			return (*((*)arr[index + _Off]));
		}

		bool operator==(const _ZArrayConstIter& _Right) const
		{	// test for iterator equality
			_Compat(_Right);
			return (this->arr == _Right.arr && index == _Right.index);
		}

		bool operator!=(const _ZArrayConstIter& _Right) const
		{	// test for iterator inequality
			return (!(*this == _Right));
		}

		bool operator<(const _ZArrayConstIter& _Right) const
		{	// test if this < _Right
			_Compat(_Right);
			return (this->index < _Right.index);
		}

		bool operator>(const _ZArrayConstIter& _Right) const
		{	// test if this > _Right
			return (_Right < *this);
		}

		bool operator<=(const _ZArrayConstIter& _Right) const
		{	// test if this <= _Right
			return (!(_Right < *this));
		}

		bool operator>=(const _ZArrayConstIter& _Right) const
		{	// test if this >= _Right
			return (!(*this < _Right));
		}

		void _Compat(const _ZArrayConstIter& _Right) const
		{	// test for compatible iterator pair
			if (_Right.arr != arr)
			{	// report error
				throw ("array iterators incompatible");
			}
		}
	protected:
		size_type index;
		const_pointer arr;
	};

	template<class _ZArray>
	class ArrayIterator
		: public ArrayConstIterator < _ZArray >
	{
	public:

		typedef ArrayIterator<_ZArray> _ZArrayIter;
		typedef ArrayConstIterator<_ZArray> _ZIterBase;


		typedef typename _ZArray::value_type value_type;
		typedef typename _ZArray::difference_type difference_type;
		typedef typename _ZArray::pointer pointer;
		typedef typename _ZArray::reference reference;


		ArrayIterator()
			:ArrayConstIterator < _ZArray >()
		{

		}
		ArrayIterator(size_type index, pointer arr)
			:ArrayConstIterator < _ZArray >(index,arr)
		{
			this->arr = arr;
		}

		reference operator*() const
		{
			if (nullptr == arr)
			{
				throw "array iterator not incrementable";
			}
			if (index >= arr->length())
			{
				throw "index out of range";
			}
			return (*arr)[index];
		}

		pointer operator->() const
		{	// return pointer to class object
			return (_STD pointer_traits<pointer>::pointer_to(**this));
		}


		_ZArrayIter& operator++()
		{
			++*(_ZIterBase*)this;
			return *this;
		}

		_ZArrayIter& operator++(int)
		{
			// postincrement
			_ZArrayIter tmp = *this;
			++*this;
			return tmp;
		}

		_ZArrayIter& operator--()
		{
			--*(_ZIterBase)this;
			return *this;
		}
		_ZArrayIter& operator--(int)
		{
			_ZArrayIter tmp = *this;
			--*this;
			return tmp;
		}

		_ZArrayIter& operator+=(difference_type _off)
		{
			// increment by integer
			*(_ZIterBase)this += _off;
			return *this;
		}

		_ZArrayIter operator+(difference_type _Off) const
		{	// return this + integer
			_ZArrayIter _Tmp = *this;
			return (_Tmp += _Off);
		}

		_ZArrayIter& operator-=(difference_type _Off)
		{	// decrement by integer
			return (*this += -_Off);
		}

		_ZArrayIter operator-(difference_type _Off) const
		{	// return this - integer
			_ZArrayIter _Tmp = *this;
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
			pointer arr;
	};

	template <class T>
	class Array
	{

	public:
		typedef Array<T> _ZArray;

		typedef typename T value_type;
		typedef typename int difference_type;
		typedef typename const  _ZArray* const_pointer;
		typedef typename T& reference;
		typedef typename const T& const_reference;
		typedef typename _ZArray * pointer;
		typedef typename size_t size_type;


		typedef ArrayConstIterator<_ZArray> const_iterator;
		typedef ArrayIterator<_ZArray> iterator;
		Array(size_type len)
			:size(len)
		{
			assert(len > 0);
			alloc(len);
		}
		Array(const Array& arr)
		{
			alloc(size);
			size = arr.size;
			copy(arr.data);
		}
		virtual ~Array()
		{
			deleteArray<T>(data);
		}
		size_type length() const
		{
			return size;
		}
		_ZArray& operator=(const _ZArray& arr)
		{
			if (this != &arr)
			{
				deleteArray<T>(data);
				size = arr.size;
				copy(arr.data);
			}
			return *this;
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
			return const_iterator(0,this);
		}

		const_iterator cend() const _NOEXCEPT
		{
			return const_iterator(size, this);
		}

		iterator begin() _NOEXCEPT
		{
			return iterator(0, this);
		}

		iterator end() _NOEXCEPT
		{
			return iterator(size, this);
		}
	protected:
		void alloc(size_type size)
		{
			data = new T[size];
		}
		void copy(const T* src)
		{
			for (size_type i = 0; i < size; i++)
			{
				data[i] = src[i];
			}
		}
	protected:
		size_type size;
		T* data;
	};
}