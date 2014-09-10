#include "stdafx.h"
#include "ZString.h"

namespace veda
{
#pragma warning(push)
#pragma warning(disable:4996)
	String::String()
		:mCapacity(DEFAULT_SIZE), mSize(0), mData(mBuf)
	{
		mBuf[0] = '\0';
	}
	String::String(tchar c)
		:mCapacity(DEFAULT_SIZE), mSize(0), mData(mBuf)
	{
		mBuf[0] = '\0';
		append(c);
	}
	String::String(const tchar* str)
		: mCapacity(DEFAULT_SIZE), mSize(0), mData(mBuf)
	{
		mBuf[0] = '\0';
		append(str);
	}
	String::String(const String& str)
		: mCapacity(DEFAULT_SIZE), mSize(0), mData(mBuf)
	{
		mBuf[0] = '\0';
		append(str);
	}
	String::String(String&& str)
		: mCapacity(DEFAULT_SIZE), mSize(0), mData(mBuf)
	{
		mBuf[0] = '\0';
		if (str.isDefaultBuffer())
		{
			append(str.mBuf);
		}
		else
		{
			mBuf[0] = '\0';
			if (!isDefaultBuffer())
			{
				delete mData;
			}
		}
		mData = str.mData;
		mCapacity = str.mCapacity;
		mSize = str.mSize;
		str.mData = str.mBuf;
	}

	String::String(int v)
		: mCapacity(DEFAULT_SIZE), mSize(0), mData(mBuf)
	{
		mBuf[0] = '\0';
		append(v);
	}
	String::String(unsigned int v)
		: mCapacity(DEFAULT_SIZE), mSize(0), mData(mBuf)
	{
		mBuf[0] = '\0';
		append(v);
	}
	String::String(__int64 v)
		: mCapacity(DEFAULT_SIZE), mSize(0), mData(mBuf)
	{
		mBuf[0] = '\0';
		append(v);
	}
	String::String(unsigned __int64 v)
		: mCapacity(DEFAULT_SIZE), mSize(0), mData(mBuf)
	{
		mBuf[0] = '\0';
		append(v);
	}
	String::String(short v)
		: mCapacity(DEFAULT_SIZE), mSize(0), mData(mBuf)
	{
		mBuf[0] = '\0';
		append(v);
	}
	String::String(unsigned short v)
		: mCapacity(DEFAULT_SIZE), mSize(0), mData(mBuf)
	{
		mBuf[0] = '\0';
		append(v);
	}
	String::String(long v)
		: mCapacity(DEFAULT_SIZE), mSize(0), mData(mBuf)
	{
		mBuf[0] = '\0';
		append(v);
	}
	String::String(unsigned long v)
		: mCapacity(DEFAULT_SIZE), mSize(0), mData(mBuf)
	{
		mBuf[0] = '\0';
		append(v);
	}
	String::String(float v)
		: mCapacity(DEFAULT_SIZE), mSize(0), mData(mBuf)
	{
		mBuf[0] = '\0';
		append(v);
	}
	String::String(double v)
		: mCapacity(DEFAULT_SIZE), mSize(0), mData(mBuf)
	{
		mBuf[0] = '\0';
		append(v);
	}
	String::String(long double v)
		: mCapacity(DEFAULT_SIZE), mSize(0), mData(mBuf)
	{
		mBuf[0] = '\0';
		append(v);
	}

	String::~String()
	{
		if (!isDefaultBuffer() && mData)
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
	String& String::operator = (String&& str)
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
				if (!isDefaultBuffer())
				{
					delete mData;
				}
			}
			mData = str.mData;
			mCapacity = str.mCapacity;
			mSize = str.mSize;
			str.mData = str.mBuf;
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
		StringConvert sc;
		const wchar_t *pStr = sc.char2wchar(str);
		assign(pStr, len(pStr));
		return *this;
	}
	String& String::operator += (const char* str)
	{
		append(str);
		return *this;
	}
	String& String::append(const char* str)
	{
		String tmp;
		tmp = str;
		append(tmp);
		return *this;
	}
#else
	String& String::operator = (const wchar_t* str)
	{
		StringConvert sc;
		const char *pStr = sc.wchar2char(str);
		assign(pStr, len(pStr));
		return *this;
	}
	String& String::operator += (const wchar_t* str)
	{
		append(str);
		return *this;
	}
	String& String::append(const wchar_t* str)
	{
		String tmp;
		tmp = str;
		append(tmp);
		return *this;
	}
#endif
	String& String::operator += (tchar c)
	{
		append(c);
		return *this;
	}
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

	String& String::operator += (const tchar* v)
	{
		append(v);
		return *this;
	}

	String& operator +(int v, const String& str)
	{
		String tmp(v);
		tmp.append(str);
		return std::move(tmp);
	}
	String& operator +(unsigned int v, const String& str)
	{
		String tmp(v);
		tmp.append(str);
		return std::move(tmp);
	}
	String& operator +(__int64 v, const String& str)
	{
		String tmp(v);
		tmp.append(str);
		return std::move(tmp);
	}
	String& operator +(unsigned __int64 v, const String& str)
	{
		String tmp(v);
		tmp.append(str);
		return std::move(tmp);
	}
	String& operator +(short v, const String& str)
	{
		String tmp(v);
		tmp.append(str);
		return std::move(tmp);
	}
	String& operator +(unsigned short v, const String& str)
	{
		String tmp(v);
		tmp.append(str);
		return std::move(tmp);
	}
	String& operator +(long v, const String& str)
	{
		String tmp(v);
		tmp.append(str);
		return std::move(tmp);
	}
	String& operator +(unsigned long v, const String& str)
	{
		String tmp(v);
		tmp.append(str);
		return std::move(tmp);
	}
	String& operator +(float v, const String& str)
	{
		String tmp(v);
		tmp.append(str);
		return std::move(tmp);
	}
	String& operator +(double v, const String& str)
	{
		String tmp(v);
		tmp.append(str);
		return std::move(tmp);
	}
	String& operator +(long double v, const String& str)
	{
		String tmp(v);
		tmp.append(str);
		return std::move(tmp);
	}

	String& operator +(tchar v, const String& str)
	{
		String tmp(v);
		tmp.append(str);
		return std::move(tmp);
	}
	String& operator +(const tchar* v, const String& str)
	{
		String tmp(v);
		tmp.append(str);
		return std::move(tmp);
	}
	String& operator +(const String& v, const String& str)
	{
		String tmp(v);
		tmp.append(str);
		return std::move(tmp);
	}

	String& operator +(const String& str, int v)
	{
		String tmp = str;
		tmp.append(v);
		return std::move(tmp);
	}
	String& operator +(const String& str, unsigned int v)
	{
		String tmp = str;
		tmp.append(v);
		return std::move(tmp);
	}
	String& operator +(const String& str, __int64 v)
	{
		String tmp = str;
		tmp.append(v);
		return std::move(tmp);
	}
	String& operator +(const String& str, unsigned __int64 v)
	{
		String tmp = str;
		tmp.append(v);
		return std::move(tmp);
	}
	String& operator +(const String& str, short v)
	{
		String tmp = str;
		tmp.append(v);
		return std::move(tmp);
	}
	String& operator +(const String& str, unsigned short v)
	{
		String tmp = str;
		tmp.append(v);
		return std::move(tmp);
	}
	String& operator +(const String& str, long v)
	{
		String tmp = str;
		tmp.append(v);
		return std::move(tmp);
	}
	String& operator +(const String& str, unsigned long v)
	{
		String tmp = str;
		tmp.append(v);
		return std::move(tmp);
	}
	String& operator +(const String& str, float v)
	{
		String tmp = str;
		tmp.append(v);
		return std::move(tmp);
	}
	String& operator +(const String& str, double v)
	{
		String tmp = str;
		tmp.append(v);
		return std::move(tmp);
	}
	String& operator +(const String& str, long double v)
	{
		String tmp = str;
		tmp.append(v);
		return std::move(tmp);
	}
	String& operator +(const String& str, tchar v)
	{
		String tmp = str;
		tmp.append(v);
		return std::move(tmp);
	}
	String& operator +(const String& str, const tchar* v)
	{
		String tmp = str;
		tmp.append(v);
		return std::move(tmp);
	}

	String& String::append(tchar c)
	{
		tchar buf[2] = { c };
		append(buf);
		return *this;
	}
	String& String::append(const tchar* str)
	{
		append(str, len(str));
		return *this;
	}
	String& String::append(const tchar* str, size_t size)
	{
		if (size + mSize >= mCapacity)
		{
			
			mCapacity = size + DEFAULT_SIZE;
			tchar* data = new tchar[mCapacity];
			copy(data, mData);
			cat(data, str);
			mSize += size;
			if (isDefaultBuffer())
			{
				mBuf[0] = '\0';
			}
			else
			{
				delete mData;
			}
			mData = data;
		}
		else if (!isDefaultBuffer() && size + mSize <= mCapacity / 4)
		{
			mCapacity = mCapacity / 2;
			if (mCapacity <= DEFAULT_SIZE)
			{
				mCapacity = DEFAULT_SIZE;
				copy(mBuf, mData);
				delete mData;
				mData = mBuf;
			}
			else
			{
				tchar* data = new tchar[mCapacity];
				copy(data, mData);
				cat(data, str);
				delete mData;
				mData = data;
			}
		}
		else
		{
			cat(mData, str);
		}
		return *this;
	}
	String& String::append(const String& str)
	{
		append(str.mData, str.mSize);
		return *this;
	}
	String& String::append(int v)
	{
		String tmp;
		tmp.format(_T("%d"), v);
		append(tmp);
		return *this;
	}
	String& String::append(unsigned int v)
	{
		String tmp;
		tmp.format(_T("%u"), v);
		append(tmp);
		return *this;
	}
	String& String::append(__int64 v)
	{
		String tmp;
		tmp.format(_T("%ld"), v);
		append(tmp);
		return *this;
	}
	String& String::append(unsigned __int64 v)
	{
		String tmp;
		tmp.format(_T("%u"), v);
		append(tmp);
		return *this;
	}
	String& String::append(short v)
	{
		String tmp;
		tmp.format(_T("%d"), v);
		append(tmp);
		return *this;
	}
	String& String::append(unsigned short v)
	{
		String tmp;
		tmp.format(_T("%u"), v);
		append(tmp);
		return *this;
	}
	String& String::append(long v)
	{
		String tmp;
		tmp.format(_T("%d"), v);
		append(tmp);
		return *this;
	}
	String& String::append(unsigned long v)
	{
		String tmp;
		tmp.format(_T("%u"), v);
		append(tmp);
		return *this;
	}
	String& String::append(float v)
	{
		String tmp;
		tmp.format(_T("%f"), v);
		append(tmp);
		return *this;
	}
	String& String::append(double v)
	{
		String tmp;
		tmp.format(_T("%f"), v);
		append(tmp);
		return *this;
	}
	String& String::append(long double v)
	{
		String tmp;
		tmp.format(_T("%lf"), v);
		append(tmp);
		return *this;
	}

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
		va_list argList;
		int nLen;
		va_start(argList, fmat);
		nLen = ::_vsntprintf(NULL, 0, fmat, argList);
		Array<tchar> buf(nLen + 1);
		int iRet = ::_vsntprintf(&buf[0], nLen + 1, fmat, argList);
		va_end(argList);
		assign(&buf[0], nLen);
		return *this;
	}

	size_t String::getCapacity() const
	{
		return mCapacity;
	}
	size_t String::getSize() const
	{
		return mSize;
	}
	String::operator const tchar*() const
	{
		return mData;
	}
	tchar& String::operator [](size_t index) const
	{
		return mData[index];
	}

#ifdef _UNICODE
	std::wostream& operator<<(std::wostream& os, const String& dt)
	{
		os << dt.mData;
		return os;
	}
#else
	std::ostream& operator<<(std::ostream& os, const String& dt);
	{
		os << dt.mData;
		return os;
	}
#endif

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

#pragma warning(pop)
}

