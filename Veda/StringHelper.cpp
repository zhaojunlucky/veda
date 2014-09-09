#include "stdafx.h"
#include "StringHelper.h"

namespace veda
{
	StringHelper::StringHelper(TCHAR* buf,size_t max)
		:buf(buf)
	{
		mBuf = std::make_shared<Array<TCHAR>>(max);
	}


	StringHelper::~StringHelper()
	{
	}

	TCHAR* StringHelper::get()
	{
		return buf;
	}

	StringHelper::operator TCHAR*()
	{
		return buf;
	}

	StringHelper& StringHelper::operator=(int v)
	{
		format(_T("%d"), v);
		return *this;
	}
	StringHelper& StringHelper::operator=(__int64 v)
	{
		format(_T("%ld"), v);
		return *this;
	}
	StringHelper& StringHelper::operator=(float v)
	{
		format(_T("%f"), v);
		return *this;
	}
	StringHelper& StringHelper::operator=(double v)
	{
		format(_T("%f"), v);
		return *this;
	}
	StringHelper& StringHelper::operator=(short v)
	{
		format(_T("%d"), v);
		return *this;
	}
	StringHelper& StringHelper::operator=(char v)
	{
		format(_T("%c"), v);
		return *this;
	}
	StringHelper& StringHelper::operator=(unsigned int v)
	{
		format(_T("%ud"), v);
		return *this;
	}
	StringHelper& StringHelper::operator=(unsigned __int64 v)
	{
		format(_T("%uld"), v);
		return *this;
	}
	StringHelper& StringHelper::operator=(unsigned short v)
	{
		format(_T("%ud"), v);
		return *this;
	}
	StringHelper& StringHelper::operator=(unsigned char v)
	{
		format(_T("%c"), v);
		return *this;
	}
	StringHelper& StringHelper::operator=(bool v)
	{
		format(_T("%s"), v ? _T("true") : _T("false"));
		return *this;
	}
	StringHelper& StringHelper::operator=(long v)
	{
		format(_T("%l"), v);
		return *this;
	}
	StringHelper& StringHelper::operator=(unsigned long v)
	{
		format(_T("%ul"), v);
		return *this;
	}
	StringHelper& StringHelper::operator=(long double v)
	{
		format(_T("%lf"), v);
		return *this;
	}
	StringHelper& StringHelper::operator=(const TCHAR* str)
	{
		format(_T("%s"), str);
		return *this;
	}

	StringHelper& StringHelper::operator+=(int v)
	{
		formatTemp(_T("%d"), v);
		_tcscat_s(buf,mBuf->length(), &((*mBuf.get())[0]));
		return *this;
	}
	StringHelper& StringHelper::operator+=(__int64 v)
	{
		formatTemp(_T("%ld"), v);
		_tcscat_s(buf, mBuf->length(), &((*mBuf.get())[0]));
		return *this;
	}
	StringHelper& StringHelper::operator+=(float v)
	{
		formatTemp(_T("%f"), v);
		_tcscat_s(buf, mBuf->length(), &((*mBuf.get())[0]));
		return *this;
	}
	StringHelper& StringHelper::operator+=(double v)
	{
		formatTemp(_T("%f"), v);
		_tcscat_s(buf, mBuf->length(), &((*mBuf.get())[0]));
		return *this;
	}
	StringHelper& StringHelper::operator+=(short v)
	{
		formatTemp(_T("%d"), v);
		_tcscat_s(buf, mBuf->length(), &((*mBuf.get())[0]));
		return *this;
	}
	StringHelper& StringHelper::operator+=(char v)
	{
		formatTemp(_T("%c"), v);
		_tcscat_s(buf, mBuf->length(), &((*mBuf.get())[0]));
		return *this;
	}
	StringHelper& StringHelper::operator+=(unsigned int v)
	{
		formatTemp(_T("%ud"), v);
		_tcscat_s(buf, mBuf->length(), &((*mBuf.get())[0]));
		return *this;
	}
	StringHelper& StringHelper::operator+=(unsigned __int64 v)
	{
		formatTemp(_T("%uld"), v);
		_tcscat_s(buf, mBuf->length(), &((*mBuf.get())[0]));
		return *this;
	}
	StringHelper& StringHelper::operator+=(unsigned short v)
	{
		formatTemp(_T("%ud"), v);
		_tcscat_s(buf, mBuf->length(), &((*mBuf.get())[0]));
		return *this;
	}
	StringHelper& StringHelper::operator+=(unsigned char v)
	{
		formatTemp(_T("%c"), v);
		_tcscat_s(buf, mBuf->length(), &((*mBuf.get())[0]));
		return *this;
	}
	StringHelper& StringHelper::operator+=(bool v)
	{
		formatTemp(_T("%s"), v?_T("true"):_T("false"));
		_tcscat_s(buf, mBuf->length(), &((*mBuf.get())[0]));
		return *this;
	}
	StringHelper& StringHelper::operator+=(long v)
	{
		formatTemp(_T("%l"), v);
		_tcscat_s(buf, mBuf->length(), &((*mBuf.get())[0]));
		return *this;
	}
	StringHelper& StringHelper::operator+=(unsigned long v)
	{
		formatTemp(_T("%ul"), v);
		_tcscat_s(buf, mBuf->length(), &((*mBuf.get())[0]));
		return *this;
	}
	StringHelper& StringHelper::operator+=(long double v)
	{
		formatTemp(_T("%lf"), v);
		_tcscat_s(buf, mBuf->length(), &((*mBuf.get())[0]));
		return *this;
	}
	StringHelper& StringHelper::operator+=(const TCHAR* str)
	{
		formatTemp(_T("%s"), str);
		_tcscat_s(buf, mBuf->length(), &((*mBuf.get())[0]));
		return *this;
	}

	StringHelper& StringHelper::format(const TCHAR* str, ...)
	{
		va_list pArgList;
		va_start(pArgList, str);
		_vstprintf_s(buf, mBuf->length(), str, pArgList);
		va_end(pArgList);
		return *this;
	}
	void StringHelper::formatTemp(const TCHAR* str, ...)
	{
		va_list pArgList;
		va_start(pArgList, str);
		_vstprintf_s(&((*mBuf.get())[0]), mBuf->length(), str, pArgList);
		va_end(pArgList);
	}
}
