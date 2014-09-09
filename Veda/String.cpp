#include "stdafx.h"
#include "String.h"

namespace veda
{
	String::String()
		:mCapacity(DEFAULT_SIZE), mSize(0), mData(mBuf), mBuf{ 0 }
	{

	}
	String::String(tchar c)
		:mCapacity(DEFAULT_SIZE), mSize(0), mData(mBuf), mBuf{ 0 }
	{
		append(c);
	}
	String::String(const tchar* str)
		: mCapacity(DEFAULT_SIZE), mSize(0), mData(mBuf), mBuf{ 0 }
	{
		append(str);
	}
	String::String(const String& str)
		: mCapacity(DEFAULT_SIZE), mSize(0), mData(mBuf), mBuf{ 0 }
	{
		append(str);
	}
	String::String(const String&& str)
		: mCapacity(DEFAULT_SIZE), mSize(0), mData(mBuf), mBuf{ 0 }
	{
		if (str.isDefaultBuffer())
		{
			append(str.mBuf);
		}
		else
		{
			mBuf[0] = '\0';
			delete mData;
		}
		mData = str.mData;
		mCapacity = str.mCapacity;
		mSize = str.mSize;
	}

	String::String(int v)
		: mCapacity(DEFAULT_SIZE), mSize(0), mData(mBuf), mBuf{ 0 }
	{
		append(v);
	}
	String::String(unsigned int v)
		: mCapacity(DEFAULT_SIZE), mSize(0), mData(mBuf), mBuf{ 0 }
	{
		append(v);
	}
	String::String(__int64 v)
		: mCapacity(DEFAULT_SIZE), mSize(0), mData(mBuf), mBuf{ 0 }
	{
		append(v);
	}
	String::String(unsigned __int64 v)
		: mCapacity(DEFAULT_SIZE), mSize(0), mData(mBuf), mBuf{ 0 }
	{
		append(v);
	}
	String::String(short v)
		: mCapacity(DEFAULT_SIZE), mSize(0), mData(mBuf), mBuf{ 0 }
	{
		append(v);
	}
	String::String(unsigned short v)
		: mCapacity(DEFAULT_SIZE), mSize(0), mData(mBuf), mBuf{ 0 }
	{
		append(v);
	}
	String::String(long v)
		: mCapacity(DEFAULT_SIZE), mSize(0), mData(mBuf), mBuf{ 0 }
	{
		append(v);
	}
	String::String(unsigned long v)
		: mCapacity(DEFAULT_SIZE), mSize(0), mData(mBuf), mBuf{ 0 }
	{
		append(v);
	}
	String::String(float v)
		: mCapacity(DEFAULT_SIZE), mSize(0), mData(mBuf), mBuf{ 0 }
	{
		append(v);
	}
	String::String(double v)
		: mCapacity(DEFAULT_SIZE), mSize(0), mData(mBuf), mBuf{ 0 }
	{
		append(v);
	}
	String::String(long double v)
		: mCapacity(DEFAULT_SIZE), mSize(0), mData(mBuf), mBuf{ 0 }
	{
		append(v);
	}

	String::~String()
	{
		if (!isDefaultBuffer())
		{
			delete mData;
		}
	}
	String& String::operator = (const String& str)
	{
		if (this != &str)
		{
			assign(str.mData, str.mSize);
		}
		return *this;
	}
	String& String::operator = (const String&& str)
	{
		if (mBuf != str.mBuf)
		{
			if (str.isDefaultBuffer())
			{
				copy(mBuf, str.mBuf);
			}
			else
			{
				mBuf[0] = '\0';
				delete mData;
			}
			mData = str.mData;
			mCapacity = str.mCapacity;
			mSize = str.mSize;
		}
		return *this;
	}
	String& String::operator = (const tchar* str)
	{
		if (mData != str)
		{
			assign(str, len(str));
		}
		return *this;
	}
	String& String::operator = (const tchar tc)
	{
		if (!isDefaultBuffer())
		{
			delete mData;
			mData = mBuf;
		}

		mData[0] = tc;
		mData[1] = '\0';
		return *this;
	}

	String& String::operator =(int v)
	{
		String tmp(v);
		*this = std::move(tmp);
		return *this;
	}
	String& String::operator =(unsigned int v)
	{
		String tmp(v);
		*this = std::move(tmp);
		return *this;
	}
	String& String::operator =(__int64 v)
	{
		String tmp(v);
		*this = std::move(tmp);
		return *this;
	}
	String& String::operator =(unsigned __int64 v)
	{
		String tmp(v);
		*this = std::move(tmp);
		return *this;
	}
	String& String::operator =(short v)
	{
		String tmp(v);
		*this = std::move(tmp);
		return *this;
	}
	String& String::operator =(unsigned short v)
	{
		String tmp(v);
		*this = std::move(tmp);
		return *this;
	}
	String& String::operator =(long v)
	{
		String tmp(v);
		*this = std::move(tmp);
		return *this;
	}
	String& String::operator =(unsigned long v)
	{
		String tmp(v);
		*this = std::move(tmp);
		return *this;
	}
	String& String::operator =(float v)
	{
		String tmp(v);
		*this = std::move(tmp);
		return *this;
	}
	String& String::operator =(double v)
	{
		String tmp(v);
		*this = std::move(tmp);
		return *this;
	}
	String& String::operator =(long double v)
	{
		String tmp(v);
		*this = std::move(tmp);
		return *this;
	}

#ifdef _UNICODE
	String& String::operator = (const char* str)
	{

	}
	String& String::operator += (const char* str)
	{
		append(str);
		return *this;
	}
	String& String::append(const char* str)
	{

	}
#else
	String& String::operator = (const wchar_t* str);
	String& String::operator += (const wchar_t* str)
	{
		append(str);
		return *this;
	}
	String& String::append(const wchar_t* str);
#endif
	String& String::operator +=(int v)
	{
		append(v);
		return *this;
	}
	String& String::operator +=(unsigned int v)
	{
		append(v);
		return *this;
	}
	String& String::operator +=(__int64 v)
	{
		append(v);
		return *this;
	}
	String& String::operator +=(unsigned __int64 v)
	{
		append(v);
		return *this;
	}
	String& String::operator +=(short v)
	{
		append(v);
		return *this;
	}
	String& String::operator +=(unsigned short v)
	{
		append(v);
		return *this;
	}
	String& String::operator +=(long v)
	{
		append(v);
		return *this;
	}
	String& String::operator +=(unsigned long v)
	{
		append(v);
		return *this;
	}
	String& String::operator +=(float v)
	{
		append(v);
		return *this;
	}
	String& String::operator +=(double v)
	{
		append(v);
		return *this;
	}
	String& String::operator +=(long double v)
	{
		append(v);
		return *this;
	}

	String& operator +=(int v, const String& str)
	{
		String tmp(v);
		tmp.append(str);
		return std::move(tmp);
	}
	String& operator +=(unsigned int v, const String& str)
	{
		String tmp(v);
		tmp.append(str);
		return std::move(tmp);
	}
	String& operator +=(__int64 v, const String& str)
	{
		String tmp(v);
		tmp.append(str);
		return std::move(tmp);
	}
	String& operator +=(unsigned __int64 v, const String& str)
	{
		String tmp(v);
		tmp.append(str);
		return std::move(tmp);
	}
	String& operator +=(short v, const String& str)
	{
		String tmp(v);
		tmp.append(str);
		return std::move(tmp);
	}
	String& operator +=(unsigned short v, const String& str)
	{
		String tmp(v);
		tmp.append(str);
		return std::move(tmp);
	}
	String& operator +=(long v, const String& str)
	{
		String tmp(v);
		tmp.append(str);
		return std::move(tmp);
	}
	String& operator +=(unsigned long v, const String& str)
	{
		String tmp(v);
		tmp.append(str);
		return std::move(tmp);
	}
	String& operator +=(float v, const String& str)
	{
		String tmp(v);
		tmp.append(str);
		return std::move(tmp);
	}
	String& operator +=(double v, const String& str)
	{
		String tmp(v);
		tmp.append(str);
		return std::move(tmp);
	}
	String& operator +=(long double v, const String& str)
	{
		String tmp(v);
		tmp.append(str);
		return std::move(tmp);
	}

	String& String::append(tchar c);
	String& String::append(const tchar* str);
	String& String::append(const tchar* str, size_t size);
	String& String::append(const String& str);
	String& String::append(int v);
	String& String::append(unsigned int v);
	String& String::append(__int64 v);
	String& String::append(unsigned __int64 v);
	String& String::append(short v);
	String& String::append(unsigned short v);
	String& String::append(long v);
	String& String::append(unsigned long v);
	String& String::append(float v);
	String& String::append(double v);
	String& String::append(long double v);

	bool String::equals(const tchar* str) const
	{
		return compare(str) == 0;
	}
	bool String::equals(const String& str) const
	{
		return compare(str) == 0;
	}
	bool String::equalsIgnoreCase(const tchar* str) const
	{
		return compareIgnoreCase(str) == 0;
	}
	bool String::equalsIgnoreCase(const String& str) const
	{
		return compareIgnoreCase(str) == 0;
	}

	int String::compare(const tchar* str) const
	{
		return cmpstr(mData, str);
	}
	int String::compare(const String& str) const
	{
		return compare(str.mData);
	}
	int String::compareIgnoreCase(const tchar* str) const
	{
		return cmpicase(mData, str);
	}
	int String::compareIgnoreCase(const String& str) const
	{
		return compareIgnoreCase(str.mData);
	}

	bool String::operator==(const tchar* str) const
	{
		return equalsIgnoreCase(str);
	}
	bool String::operator==(const String& str) const
	{
		return equalsIgnoreCase(str);
	}

	bool operator==(const tchar* str, const String& str2)
	{
		return (str2 == str);
	}

	String& String::format(const tchar* fmat, ...)
	{

	}

	size_t String::getCapacity() const
	{
		return mCapacity;
	}
	size_t String::getSize() const
	{
		return mSize;
	}
	String::operator tchar*()
	{
		return mData;
	}
	tchar& String::operator [](size_t index)
	{
		return mData[index];
	}

	void String::assign(const tchar* buf, size_t size)
	{
		if (size >= mCapacity)
		{
			mCapacity = size + DEFAULT_SIZE;
			if (isDefaultBuffer())
			{
				mBuf[0] = '\0';
			}
			else
			{
				delete mData;
			}
			mData = new tchar[mCapacity];
		}
		else if (!isDefaultBuffer() && size <= mCapacity / 4)
		{
			mCapacity = mCapacity / 2;
			if (mCapacity <= DEFAULT_SIZE)
			{
				mCapacity = DEFAULT_SIZE;
				delete mData;
				mData = mBuf;
			}
			else
			{
				delete mData;
				mData = new tchar[mCapacity];
			}
		}
		copy(mData, buf);
		mSize = size;
	}

	bool String::isDefaultBuffer() const
	{
		return (mData == mBuf);
	}


}

