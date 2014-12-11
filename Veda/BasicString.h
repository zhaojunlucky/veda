#pragma once

#include <stdarg.h>
#include <Array.h>
#include <iostream>
#include <memory>
#include "StringTraits.h"
#include <tchar.h>
#include <StringFind.h>
#include "veda.h"

namespace veda
{
#pragma warning(push)
#pragma warning(disable:4996)
#define DEFAULT_SIZE 64

	template<class _traits, class _ochar>
	class VEDA_EXPORT BasicString
	{
	public:
		typedef typename _traits::value_type value_type;
		typedef typename _traits::size_type size_type;
		typedef BasicString<_traits, _ochar> _String;
	public:
		static const size_type npos = -1;
		typedef std::shared_ptr<BasicString<_traits, _ochar>> StringPtr;
		
		BasicString()
			:mCapacity(DEFAULT_SIZE), mSize(0)
		{
			mData = alloc(DEFAULT_SIZE);
		}

		
		BasicString(value_type c)
			: mCapacity(0), mSize(0), mData(0)
		{
			append(c);
		}

		
		BasicString(const value_type* str)
			: mCapacity(0), mSize(0), mData(0)
		{
			append(str);
		}
		
		BasicString(const _String& str)
			: mCapacity(0), mSize(0), mData(0)
		{
			append(str);
		}
		
		BasicString(_String&& str)
		{
			*this = std::move(str);
		}

		
		BasicString(int v)
			: mCapacity(0), mSize(0), mData(0)
		{
			append(v);
		}
		
		BasicString(unsigned int v)
			: mCapacity(0), mSize(0), mData(0)
		{
			append(v);
		}
		
		BasicString(__int64 v)
			: mCapacity(0), mSize(0), mData(0)
		{
			append(v);
		}
		
		BasicString(unsigned __int64 v)
			: mCapacity(0), mSize(0), mData(0)
		{
			append(v);
		}
		
		BasicString(short v)
			: mCapacity(0), mSize(0), mData(0)
		{
			append(v);
		}
		
		BasicString(unsigned short v)
			: mCapacity(0), mSize(0), mData(0)
		{
			append(v);
		}
		
		BasicString(long v)
			: mCapacity(0), mSize(0), mData(0)
		{
			append(v);
		}
		
		BasicString(unsigned long v)
			: mCapacity(0), mSize(0), mData(0)
		{
			append(v);
		}
		
		BasicString(float v)
			: mCapacity(0), mSize(0), mData(0)
		{
			append(v);
		}
		
		BasicString(double v)
			: mCapacity(0), mSize(0), mData(0)
		{
			append(v);
		}
		
		BasicString(long double v)
			: mCapacity(0), mSize(0), mData(0)
		{
			append(v);
		}

		
		~BasicString()
		{
			if (mData)
			{
				delete mData;
				mData = 0;
			}

			//printf("destructor:%d\n", (int)mData);
		}
		
		_String& operator = (const _String& str)
		{
			if (this != &str)
			{
				assign(str.mData, str.mSize);
			}
			return *this;
		}
		
		_String& operator = (_String&& str)
		{
			if (this != &str)
			{
				mCapacity = str.mCapacity;
				mSize = str.mSize;
				mData = str.mData;
				str.mData = 0;
			}
			return *this;
		}
		
		_String& operator = (const value_type* str)
		{
			if (mData != str)
			{
				assign(str, _traits::_len(str));
			}
			return *this;
		}
		
		_String& operator = (const value_type tc)
		{
			value_type buf[2] = { tc };
			assign(buf, 1);
			return *this;
		}
		
		_String& operator =(int v)
		{
			BasicString tmp(v);
			*this = std::move(tmp);
			return *this;
		}
		
		_String& operator =(unsigned int v)
		{
			BasicString tmp(v);
			*this = std::move(tmp);
			return *this;
		}
		
		_String& operator =(__int64 v)
		{
			BasicString tmp(v);
			*this = std::move(tmp);
			return *this;
		}
		
		_String& operator =(unsigned __int64 v)
		{
			BasicString tmp(v);
			*this = std::move(tmp);
			return *this;
		}
		
		_String& operator =(short v)
		{
			BasicString tmp(v);
			*this = std::move(tmp);
			return *this;
		}
		
		_String& operator =(unsigned short v)
		{
			BasicString tmp(v);
			*this = std::move(tmp);
			return *this;
		}
		
		_String& operator =(long v)
		{
			BasicString tmp(v);
			*this = std::move(tmp);
			return *this;
		}
		
		_String& operator =(unsigned long v)
		{
			BasicString tmp(v);
			*this = std::move(tmp);
			return *this;
		}
		
		_String& operator =(float v)
		{
			BasicString tmp(v);
			*this = std::move(tmp);
			return *this;
		}
		
		_String& operator =(double v)
		{
			BasicString tmp(v);
			*this = std::move(tmp);
			return *this;
		}
		
		_String& operator =(long double v)
		{
			BasicString tmp(v);
			*this = std::move(tmp);
			return *this;
		}
		
		_String& operator += (value_type c)
		{
			append(c);
			return *this;
		}
		
		_String& operator +=(int v)
		{
			append(v);
			return *this;
		}
		
		_String& operator +=(unsigned int v)
		{
			append(v);
			return *this;
		}
		
		_String& operator +=(__int64 v)
		{
			append(v);
			return *this;
		}
		
		_String& operator +=(unsigned __int64 v)
		{
			append(v);
			return *this;
		}
		
		_String& operator +=(short v)
		{
			append(v);
			return *this;
		}
		
		_String& operator +=(unsigned short v)
		{
			append(v);
			return *this;
		}
		
		_String& operator +=(long v)
		{
			append(v);
			return *this;
		}
		
		_String& operator +=(unsigned long v)
		{
			append(v);
			return *this;
		}
		
		_String& operator +=(float v)
		{
			append(v);
			return *this;
		}
		
		_String& operator +=(double v)
		{
			append(v);
			return *this;
		}
		
		_String& operator +=(long double v)
		{
			append(v);
			return *this;
		}
		
		_String& operator += (const value_type* v)
		{
			append(v);
			return *this;
		}

		friend StringPtr operator +(int v, const BasicString& str)
		{
			StringPtr tmp = std::make_shared<BasicString>(v);
			tmp->append(str);
			return tmp;
		}
		friend StringPtr operator +(unsigned int v, const BasicString& str)
		{
			StringPtr tmp = std::make_shared<BasicString>(v);
			tmp->append(str);
			return tmp;
		}
		friend StringPtr operator +(__int64 v, const BasicString& str)
		{
			StringPtr tmp = std::make_shared<BasicString>(v);
			tmp->append(str);
			return tmp;
		}
		friend StringPtr operator +(unsigned __int64 v, const BasicString& str)
		{
			StringPtr tmp = std::make_shared<BasicString>(v);
			tmp->append(str);
			return tmp;
		}
		friend StringPtr operator +(short v, const BasicString& str)
		{
			StringPtr tmp = std::make_shared<BasicString>(v);
			tmp->append(str);
			return tmp;
		}
		friend StringPtr operator +(unsigned short v, const BasicString& str)
		{
			StringPtr tmp = std::make_shared<BasicString>(v);
			tmp->append(str);
			return tmp;
		}
		friend StringPtr operator +(long v, const BasicString& str)
		{
			StringPtr tmp = std::make_shared<BasicString>(v);
			tmp->append(str);
			return tmp;
		}
		friend StringPtr operator +(unsigned long v, const BasicString& str)
		{
			StringPtr tmp = std::make_shared<BasicString>(v);
			tmp->append(str);
			return tmp;
		}
		friend StringPtr operator +(float v, const BasicString& str)
		{
			StringPtr tmp = std::make_shared<BasicString>(v);
			tmp->append(str);
			return tmp;
		}
		friend StringPtr operator +(double v, const BasicString& str)
		{
			StringPtr tmp = std::make_shared<BasicString>(v);
			tmp->append(str);
			return tmp;
		}
		friend StringPtr operator +(long double v, const BasicString& str)
		{
			StringPtr tmp = std::make_shared<BasicString>(v);
			tmp->append(str);
			return tmp;
		}

		friend StringPtr operator +(value_type v, const BasicString& str)
		{
			StringPtr tmp = std::make_shared<BasicString>(v);
			tmp->append(str);
			return tmp;
		}
		friend StringPtr operator +(const value_type* v, const BasicString& str)
		{
			StringPtr tmp = std::make_shared<BasicString>(v);
			tmp->append(str);
			return tmp;
		}
		friend StringPtr operator +(const BasicString& v, const BasicString& str)
		{
			StringPtr tmp = std::make_shared<BasicString>(v);
			tmp->append(str);
			return tmp;
		}

		friend StringPtr operator +(const BasicString& str, int v)
		{
			StringPtr tmp = std::make_shared<BasicString>(str);
			tmp->append(v);
			return tmp;
		}
		friend StringPtr operator +(const BasicString& str, unsigned int v)
		{
			StringPtr tmp = std::make_shared<BasicString>(str);
			tmp->append(v);
			return tmp;
		}
		friend StringPtr operator +(const BasicString& str, __int64 v)
		{
			StringPtr tmp = std::make_shared<BasicString>(str);
			tmp->append(v);
			return tmp;
		}
		friend StringPtr operator +(const BasicString& str, unsigned __int64 v)
		{
			StringPtr tmp = std::make_shared<BasicString>(str);
			tmp->append(v);
			return tmp;
		}
		friend StringPtr operator +(const BasicString& str, short v)
		{
			StringPtr tmp = std::make_shared<BasicString>(str);
			tmp->append(v);
			return tmp;
		}
		friend StringPtr operator +(const BasicString& str, unsigned short v)
		{
			StringPtr tmp = std::make_shared<BasicString>(str);
			tmp->append(v);
			return tmp;
		}
		friend StringPtr operator +(const BasicString& str, long v)
		{
			StringPtr tmp = std::make_shared<BasicString>(str);
			tmp->append(v);
			return tmp;
		}
		friend StringPtr operator +(const BasicString& str, unsigned long v)
		{
			StringPtr tmp = std::make_shared<BasicString>(str);
			tmp->append(v);
			return tmp;
		}
		friend StringPtr operator +(const BasicString& str, float v)
		{
			StringPtr tmp = std::make_shared<BasicString>(str);
			tmp->append(v);
			return tmp;
		}
		friend StringPtr operator +(const BasicString& str, double v)
		{
			StringPtr tmp = std::make_shared<BasicString>(str);
			tmp->append(v);
			return tmp;
		}
		friend StringPtr operator +(const BasicString& str, long double v)
		{
			StringPtr tmp = std::make_shared<BasicString>(str);
			tmp->append(v);
			return tmp;
		}
		friend StringPtr operator +(const BasicString& str, value_type v)
		{
			StringPtr tmp = std::make_shared<BasicString>(str);
			tmp->append(v);
			return tmp;
		}
		friend StringPtr operator +(const BasicString& str, const value_type* v)
		{
			StringPtr tmp = std::make_shared<BasicString>(str);
			tmp->append(v);
			return tmp;
		}
		
		_String append(value_type c)
		{
			value_type buf[2] = { c };
			append(buf);
			return *this;
		}
		
		_String& append(const value_type* str)
		{
			append(str, _traits::_len(str));
			return *this;
		}
		
		_String& append(const value_type* str, size_t size)
		{
			if (size + mSize >= mCapacity)
			{

				mCapacity = size + DEFAULT_SIZE;
				value_type* data = alloc(mCapacity);
				if (mData)
				{
					_traits::_copy(data, mData);
				}


				if (mData)
				{
					delete mData;
				}
				mData = data;
			}
			_traits::_ncat(mData, str, size);

			mSize += size;
			mData[mSize] = '\0';
			return *this;
		}
		
		_String& append(const _String& str)
		{
			append(str.mData, str.mSize);
			return *this;
		}
		
		_String& append(int v)
		{
			BasicString tmp;
			tmp.format(_traits::_intFormat, v);
			append(tmp);
			return *this;
		}
		
		_String& append(unsigned int v)
		{
			BasicString tmp;
			tmp.format(_traits::_uIntFormat, v);
			append(tmp);
			return *this;
		}
		
		_String& append(__int64 v)
		{
			BasicString tmp;
			tmp.format(_traits::_lIntFormat, v);
			append(tmp);
			return *this;
		}
		
		_String& append(unsigned __int64 v)
		{
			BasicString tmp;
			tmp.format(_traits::_uIntFormat, v);
			append(tmp);
			return *this;
		}
		
		_String& append(short v)
		{
			BasicString tmp;
			tmp.format(_traits::_intFormat, v);
			append(tmp);
			return *this;
		}
		
		_String& append(unsigned short v)
		{
			BasicString tmp;
			tmp.format(_traits::_uIntFormat, v);
			append(tmp);
			return *this;
		}
		
		_String& append(long v)
		{
			BasicString tmp;
			tmp.format(_traits::_lIntFormat, v);
			append(tmp);
			return *this;
		}
		
		_String& append(unsigned long v)
		{
			BasicString tmp;
			tmp.format(_traits::_uIntFormat, v);
			append(tmp);
			return *this;
		}
		
		_String& append(float v)
		{
			BasicString tmp;
			tmp.format(_traits::_floatFormat, v);
			append(tmp);
			return *this;
		}
		
		_String& append(double v)
		{
			BasicString tmp;
			tmp.format(_traits::_floatFormat, v);
			append(tmp);
			return *this;
		}
		
		_String& append(long double v)
		{
			BasicString tmp;
			tmp.format(_traits::_lFloatFormat, v);
			append(tmp);
			return *this;
		}
		void from(const _ochar* str)
		{
			std::shared_ptr<Array<value_type>> p = _traits::from(str);
			assign(&(*p.get())[0], p->length());
		}
		void from(const _ochar* str,size_type size)
		{
			std::shared_ptr<Array<value_type>> p = _traits::from(str, size);
			assign(&(*p.get())[0], p->length());
		}
		bool equals(const value_type* str) const
		{
			return compare(str) == 0;
		}
		
		bool equals(const _String& str) const
		{
			return compare(str) == 0;
		}
		
		bool equalsIgnoreCase(const value_type* str) const
		{
			return compareIgnoreCase(str) == 0;
		}
		
		bool equalsIgnoreCase(const _String& str) const
		{
			return compareIgnoreCase(str) == 0;
		}
		
		int compare(const value_type* str) const
		{
			return _traits::_cmpstr(mData, str);
		}
		
		int compare(const _String& str) const
		{
			return compare(str.mData);
		}
		
		int compareIgnoreCase(const value_type* str) const
		{
			return _traits::_cmpicase(mData, str);
		}
		
		int compareIgnoreCase(const _String& str) const
		{
			return compareIgnoreCase(str.mData);
		}
		
		bool operator==(const value_type* str) const
		{
			return equalsIgnoreCase(str);
		}
		
		bool operator==(const _String& str) const
		{
			return equalsIgnoreCase(str);
		}
		
		friend bool operator==(const value_type* str, const _String& str2)
		{
			return (str2 == str);
		}
		
		_String& format(const value_type* fmat, ...)
		{
			va_list argList;
			int nLen;
			va_start(argList, fmat);
			nLen = _traits::format(NULL, 0, fmat, argList);
			Array<value_type> buf(nLen + 1);
			int iRet = _traits::format(&buf[0], nLen + 1, fmat, argList);
			va_end(argList);
			assign(&buf[0], nLen);
			return *this;
		}
		
		size_t getCapacity() const
		{
			return mCapacity;
		}
		
		size_t getSize() const
		{
			return mSize;
		}
		
		operator const value_type*() const
		{
			return mData;
		}
		
		const value_type* getData() const
		{
			return mData;
		}
		
		const value_type* c_str() const
		{
			return mData;
		}
		
		value_type& operator [](size_t index) const
		{
			return mData[index];
		}
		
		void clear()
		{
			mSize = 0;
			mData[0] = '\0';
		}

		size_type find(value_type c, size_type start = 0) const
		{
			for (size_type i = start; i < mSize; i++)
			{
				if (c == mData[i])
				{
					return i;
				}
			}
			return npos;
		}
		
		size_type rfind(value_type c, size_type start) const
		{
			for (size_type i = start; i >= 1; i--)
			{
				if (c == mData[i])
				{
					return i;
				}
			}
			if (c == mData[0])
			{
				return 0;
			}
			else
			{
				return npos;
			}
		}
		
		size_type rfind(value_type c) const
		{
			return rfind(c, mSize - 1);
		}

		size_type find(const value_type* str, size_type size) const
		{
			return findSubStr<value_type>(mData, mSize, str, size);
		}
		size_type find(const value_type* str) const
		{
			return findSubStr<value_type>(mData, mSize, str, _traits::_len(str));
		}
		size_type find(const _String& str) const
		{
			return find(str.mData,str.mSize);
		}
		SubStringIndexesPtr findAll(const value_type* str, size_type size) const
		{
			return findAllSubStr<value_type>(mData, mSize, str, size);
		}
		SubStringIndexesPtr findAll(const value_type* str) const
		{
			return findAllSubStr<value_type>(mData, mSize, str, _traits::_len(str));
		}

		SubStringIndexesPtr findAll(const _String& str) const
		{
			return findAll(str.mData, str.mSize);
		}
		
		size_type rfind(const value_type* str, size_type size) const
		{
			return rfindSubStr<value_type>(mData, mSize, str, size);
		}
		size_type rfind(const value_type* str) const
		{
			return rfindSubStr<value_type>(mData, mSize, str, _traits::_len(str));
		}
		size_type rfind(const _String& str) const
		{
			return rfind(str.mData, str.mSize);
		}
		SubStringIndexesPtr rfindAll(const value_type* str, size_type size) const
		{
			return rfindAllSubStr<value_type>(mData, mSize, str, size);
		}
		SubStringIndexesPtr rfindAll(const value_type* str) const
		{
			return rfindAllSubStr<value_type>(mData, mSize, str, _traits::_len(str));
		}

		SubStringIndexesPtr rfindAll(const _String& str) const
		{
			return rfindAll(str.mData, str.mSize);
		}

		StringPtr trim() const
		{
			StringPtr tmp = std::make_shared<BasicString>();

			if (mSize == 0)
			{
				return tmp;
			}
			size_t i = 0;
			while (i < mSize && _traits::_isSpace(mData[i]))
			{
				i++;
			}

			size_t end = mSize - 1;

			while (end >= 1 && _traits::_isSpace(mData[end]))
			{
				end--;
			}
			if (!_traits::_isSpace(mData[end]))
			{
				tmp->assign(&mData[i], end - i + 1);
			}

			return tmp;
		}
		
		StringPtr trimLeft() const
		{
			StringPtr tmp = std::make_shared<BasicString>();
			if (mSize == 0)
			{
				return tmp;
			}
			size_t i = 0;
			while (i < mSize && _traits::_isSpace(mData[i]))
			{
				i++;
			}

			if (i < mSize)
			{
				tmp->assign(&mData[i], mSize - i + 1);
			}
			return (tmp);
		}
		
		StringPtr trimRight() const
		{
			StringPtr tmp = std::make_shared<BasicString>();
			if (mSize == 0)
			{
				return tmp;
			}
			size_t end = mSize - 1;

			while (end >= 1 && _traits::_isSpace(mData[end]))
			{
				end--;
			}

			if (!_traits::_isSpace(mData[end]))
			{
				tmp->assign(&mData[0], end + 1);
			}
			return tmp;
		}

		StringPtr toLowercase() const
		{
			_String* tmp = new _String(*this);

			for (size_type i = 0; i < tmp->mSize; i++)
			{
				tmp->mData[i] = _traits::toLowercase(tmp->mData[i]);
			}
			return std::shared_ptr<_String>(tmp);
		}

		StringPtr toUppercase() const
		{
			_String* tmp = new _String(*this);

			for (size_type i = 0; i < tmp->mSize; i++)
			{
				tmp->mData[i] = _traits::toUppercase(tmp->mData[i]);
			}
			return std::shared_ptr<_String>(tmp);
		}

		StringPtr subString(size_type startIndex)
		{
			return subString(startIndex, this->getSize() - startIndex );
		}

		StringPtr subString(size_type startIndex, size_type count)
		{
			_String* tmp = new _String();
			tmp->reserve(count);

			_traits::_ncopy(tmp->mData, &mData[startIndex], count);
			tmp->mSize = count;
			
			return std::shared_ptr<_String>(tmp);
		}

		void reserve(size_type capacity)
		{
			if (capacity >= mCapacity)
			{
				mCapacity = capacity + DEFAULT_SIZE;
				value_type* buf = new value_type[mCapacity];
				_traits::_ncopy(buf, mData, mSize);
				mData = buf;
				delete mData;
			}
		}
private:
		void assign(const value_type* buf, size_type size)
		{
			if (size >= mCapacity)
			{
				mCapacity = size + DEFAULT_SIZE;
				if (mData)
				{
					delete mData;
				}

				mData = alloc(mCapacity);
			}
			else if (size = mCapacity / 2)
			{
				mCapacity = size / 2;
				if (mCapacity < DEFAULT_SIZE)
				{
					mCapacity = DEFAULT_SIZE;
				}
				if (mData)
				{
					delete mData;
				}

				mData = alloc(mCapacity);
			}

			_traits::_ncopy(mData, buf, size);
			mData[size] = '\0';
			mSize = size;
		}

		
		value_type* alloc(size_type size)
		{
			value_type* ptr = new value_type[size];
			ptr[0] = '\0';
			return ptr;
		}
	private:
		size_type mCapacity;
		size_type mSize;
		value_type* mData;
	};
#pragma warning(pop)
}


