#pragma once
namespace veda
{
	template <class value_type>
	class IBaseArrayVisitor
	{
	public:
		virtual const value_type& operator[](size_t index) const = 0;
		virtual size_t getSize() const = 0;
	};


	template <class value_type>
	class ArrayVisitor : public IBaseArrayVisitor < value_type >
	{
	public:
		ArrayVisitor(const value_type* ptr, size_t size);
		virtual const value_type& operator[](size_t index) const;
		virtual size_t getSize() const;
	private:
		const value_type* mPtr;
		size_t mSize;
	};

	template <class value_type>
	ArrayVisitor<value_type>::ArrayVisitor(const value_type* ptr, size_t size)
		:mPtr(ptr), mSize(size)
	{

	}

	template <class value_type>
	const value_type& ArrayVisitor<value_type>::operator[](size_t index) const
	{
		return mPtr[index];
	}

	template <class value_type>
	size_t ArrayVisitor<value_type>::getSize() const
	{
		return mSize;
	}

	template <class value_type>
	class ReverseArrayVisitor : public IBaseArrayVisitor < value_type >
	{
	public:
		ReverseArrayVisitor(const value_type* ptr, size_t size);
		virtual const value_type& operator[](size_t index) const;
		virtual size_t getSize() const;
	private:
		const value_type* mPtr;
		size_t mSize;
	};

	template <class value_type>
	ReverseArrayVisitor<value_type>::ReverseArrayVisitor(const value_type* ptr, size_t size)
		:mPtr(ptr), mSize(size)
	{

	}

	template <class value_type>
	const value_type& ReverseArrayVisitor<value_type>::operator[](size_t index) const
	{
		return mPtr[mSize - index - 1];
	}

	template <class value_type>
	size_t ReverseArrayVisitor<value_type>::getSize() const
	{
		return mSize;
	}

}