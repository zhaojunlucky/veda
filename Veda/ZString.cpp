#include "stdafx.h"
#include "ZString.h"

namespace veda
{
#pragma warning(push)
#pragma warning(disable:4996)

	typedef std::shared_ptr<String> StringPtr;
	String::String()
		:mCapacity(DEFAULT_SIZE), mSize(0)
	{
		mData = alloc(DEFAULT_SIZE);
	}
	String::String(tchar c)
		: mCapacity(0), mSize(0), mData(0)
	{
		append(c);
	}
	String::String(const tchar* str)
		: mCapacity(0), mSize(0), mData(0)
	{
		append(str);
	}
	String::String(const String& str)
		: mCapacity(0), mSize(0), mData(0)
	{
		append(str);
	}
	String::String(String&& str)
	{
		*this = std::move(str);
	}

	String::String(int v)
		: mCapacity(0), mSize(0), mData(0)
	{
		append(v);
	}
	String::String(unsigned int v)
		: mCapacity(0), mSize(0), mData(0)
	{
		append(v);
	}
	String::String(__int64 v)
		: mCapacity(0), mSize(0), mData(0)
	{
		append(v);
	}
	String::String(unsigned __int64 v)
		: mCapacity(0), mSize(0), mData(0)
	{
		append(v);
	}
	String::String(short v)
		: mCapacity(0), mSize(0), mData(0)
	{
		append(v);
	}
	String::String(unsigned short v)
		: mCapacity(0), mSize(0), mData(0)
	{
		append(v);
	}
	String::String(long v)
		: mCapacity(0), mSize(0), mData(0)
	{
		append(v);
	}
	String::String(unsigned long v)
		: mCapacity(0), mSize(0), mData(0)
	{
		append(v);
	}
	String::String(float v)
		: mCapacity(0), mSize(0), mData(0)
	{
		append(v);
	}
	String::String(double v)
		: mCapacity(0), mSize(0), mData(0)
	{
		append(v);
	}
	String::String(long double v)
		: mCapacity(0), mSize(0), mData(0)
	{
		append(v);
	}

	String::~String()
	{
		if (mData)
		{
			delete mData;
			mData = 0;
		}

		//printf("destructor:%d\n", (int)mData);
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
		if (this != &str)
		{
			mCapacity = str.mCapacity;
			mSize = str.mSize;
			mData = str.mData;
			str.mData = 0;
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
		tchar buf[2] = {tc};
		assign(buf, 1);
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

	StringPtr operator +(int v, const String& str)
	{
		StringPtr tmp = std::make_shared<String>(v);
		tmp->append(str);
		return tmp;
	}
	StringPtr operator +(unsigned int v, const String& str)
	{
		StringPtr tmp = std::make_shared<String>(v);
		tmp->append(str);
		return tmp;
	}
	StringPtr operator +(__int64 v, const String& str)
	{
		StringPtr tmp = std::make_shared<String>(v);
		tmp->append(str);
		return tmp;
	}
	StringPtr operator +(unsigned __int64 v, const String& str)
	{
		StringPtr tmp = std::make_shared<String>(v);
		tmp->append(str);
		return tmp;
	}
	StringPtr operator +(short v, const String& str)
	{
		StringPtr tmp = std::make_shared<String>(v);
		tmp->append(str);
		return tmp;
	}
	StringPtr operator +(unsigned short v, const String& str)
	{
		StringPtr tmp = std::make_shared<String>(v);
		tmp->append(str);
		return tmp;
	}
	StringPtr operator +(long v, const String& str)
	{
		StringPtr tmp = std::make_shared<String>(v);
		tmp->append(str);
		return tmp;
	}
	StringPtr operator +(unsigned long v, const String& str)
	{
		StringPtr tmp = std::make_shared<String>(v);
		tmp->append(str);
		return tmp;
	}
	StringPtr operator +(float v, const String& str)
	{
		StringPtr tmp = std::make_shared<String>(v);
		tmp->append(str);
		return tmp;
	}
	StringPtr operator +(double v, const String& str)
	{
		StringPtr tmp = std::make_shared<String>(v);
		tmp->append(str);
		return tmp;
	}
	StringPtr operator +(long double v, const String& str)
	{
		StringPtr tmp = std::make_shared<String>(v);
		tmp->append(str);
		return tmp;
	}

	StringPtr operator +(tchar v, const String& str)
	{
		StringPtr tmp = std::make_shared<String>(v);
		tmp->append(str);
		return tmp;
	}
	StringPtr operator +(const tchar* v, const String& str)
	{
		StringPtr tmp = std::make_shared<String>(v);
		tmp->append(str);
		return tmp;
	}
	StringPtr operator +(const String& v, const String& str)
	{
		StringPtr tmp = std::make_shared<String>(v);
		tmp->append(str);
		return tmp;
	}

	StringPtr operator +(const String& str, int v)
	{
		StringPtr tmp = std::make_shared<String>(v);
		tmp->append(str);
		return tmp;
	}
	StringPtr operator +(const String& str, unsigned int v)
	{
		StringPtr tmp = std::make_shared<String>(v);
		tmp->append(str);
		return tmp;
	}
	StringPtr operator +(const String& str, __int64 v)
	{
		StringPtr tmp = std::make_shared<String>(v);
		tmp->append(str);
		return tmp;
	}
	StringPtr operator +(const String& str, unsigned __int64 v)
	{
		StringPtr tmp = std::make_shared<String>(v);
		tmp->append(str);
		return tmp;
	}
	StringPtr operator +(const String& str, short v)
	{
		StringPtr tmp = std::make_shared<String>(v);
		tmp->append(str);
		return tmp;
	}
	StringPtr operator +(const String& str, unsigned short v)
	{
		StringPtr tmp = std::make_shared<String>(v);
		tmp->append(str);
		return tmp;
	}
	StringPtr operator +(const String& str, long v)
	{
		StringPtr tmp = std::make_shared<String>(v);
		tmp->append(str);
		return tmp;
	}
	StringPtr operator +(const String& str, unsigned long v)
	{
		StringPtr tmp = std::make_shared<String>(v);
		tmp->append(str);
		return tmp;
	}
	StringPtr operator +(const String& str, float v)
	{
		StringPtr tmp = std::make_shared<String>(v);
		tmp->append(str);
		return tmp;
	}
	StringPtr operator +(const String& str, double v)
	{
		StringPtr tmp = std::make_shared<String>(v);
		tmp->append(str);
		return tmp;
	}
	StringPtr operator +(const String& str, long double v)
	{
		StringPtr tmp = std::make_shared<String>(v);
		tmp->append(str);
		return tmp;
	}
	StringPtr operator +(const String& str, tchar v)
	{
		StringPtr tmp = std::make_shared<String>(v);
		tmp->append(str);
		return tmp;
	}
	StringPtr operator +(const String& str, const tchar* v)
	{
		StringPtr tmp = std::make_shared<String>(v);
		tmp->append(str);
		return tmp;
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
			tchar* data = alloc(mCapacity);
			if (mData)
			{
				copy(data, mData);
			}
			
			
			if (mData)
			{
				delete mData;
			}
			mData = data;
		}
		ncat(mData, str, size);
		
		mSize += size;
		mData[mSize] = '\0';
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
	const tchar* String::getData() const
	{
		return mData;
	}
	tchar& String::operator [](size_t index) const
	{
		return mData[index];
	}

	size_t String::find(tchar c, size_t start) const
	{
		for (size_t i = start; i < mSize; i++)
		{
			if (c == mData[i])
			{
				return i;
			}
		}
		return npos;
	}
	StringPtr String::trim()
	{
		StringPtr tmp = std::make_shared<String>();

		if (mSize == 0)
		{
			return tmp;
		}
		size_t i = 0;
		while (i < mSize && isSpace(mData[i]))
		{
			i++;
		}

		size_t end = mSize - 1;

		while (end >= 1 && isSpace(mData[end]))
		{
			end--;
		}
		if (!isSpace(mData[end]))
		{
			tmp->assign(&mData[i], end - i + 1);
		}

		return tmp;
	}

	StringPtr String::trimLeft()
	{
		StringPtr tmp = std::make_shared<String>();
		if (mSize == 0)
		{
			return tmp;
		}
		size_t i = 0;
		while (i < mSize && isSpace(mData[i]))
		{
			i++;
		}
		
		if (i < mSize)
		{
			tmp->assign(&mData[i], mSize - i + 1);
		}
		return (tmp);
	}
	StringPtr String::trimRight()
	{
		StringPtr tmp = std::make_shared<String>();
		if (mSize == 0)
		{
			return tmp;
		}
		size_t end = mSize - 1;

		while (end >= 1 && isSpace(mData[end]))
		{
			end--;
		}
		
		if (!isSpace(mData[end]))
		{
			tmp->assign(&mData[0], end + 1);
		}
		return tmp;
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
		if(size >= mCapacity)
		{
			mCapacity = size + DEFAULT_SIZE;
			if (mData)
			{
				delete mData;
			}
			
			mData = alloc(mCapacity);
		}
		else if (size <= mCapacity / 4)
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

		ncopy(mData, buf, size);
		mData[size] = '\0';
		mSize = size;
	}

	tchar* String::alloc(size_t size)
	{
		tchar* ptr = new tchar[size];
		ptr[0] = '\0';
		return ptr;
	}

#pragma warning(pop)
}

