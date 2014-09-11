#pragma once

#include <stdarg.h>
#include <string.h>
#include <Array.h>
#include <utility>
#include <iostream>
#include <memory>
#include "StringConvert.h"

namespace veda
{

#ifdef _UNICODE

#ifndef tchar
	typedef wchar_t  tchar;
#endif

#ifndef _T
#define _T(x) L ## x
#endif

#define _cmpstr wcscmp
#define _cmpicase wcsicmp
#define _copy wcscpy
#define _ncopy wcsncpy
#define _len wcslen
#define _cat wcscat
#define _ncat wcsncat
#define _vsntprintf     _vsnwprintf
#define _isSpace iswspace
#else

#ifndef tchar
	typedef char  tchar;
#endif

#ifndef _T
#define _T(x) x
#endif

#define _cmp strcmp
#define _cmpicase stricmp
#define _copy strcpy
#define _ncopy strncpy
#define _len strlen
#define _cat strcat
#define _ncat strncat
#define _vsntprintf     _vsnprintf
#define _isSpace isspace

#endif

#define DEFAULT_SIZE 64
#define makeStringPtr std::make_shared<String>

	class String final
	{
	public:
		typedef std::shared_ptr<String> StringPtr;
		String();
		String(tchar c);
		String(const tchar* str);
		String(const String& str);
		String(String&& str);

		String(int v);
		String(unsigned int v);
		String(__int64 v);
		String(unsigned __int64 v);
		String(short v);
		String(unsigned short v);
		String(long v);
		String(unsigned long v);
		String(float v);
		String(double v);
		String(long double v);

		~String();
		String& operator = (const String& str);
		String& operator = (String&& str);
		String& operator = (const tchar* str);
		String& operator = (const tchar tc);

		String& operator =(int v);
		String& operator =(unsigned int v);
		String& operator =(__int64 v);
		String& operator =(unsigned __int64 v);
		String& operator =(short v);
		String& operator =(unsigned short v);
		String& operator =(long v);
		String& operator =(unsigned long v);
		String& operator =(float v);
		String& operator =(double v);
		String& operator =(long double v);

#ifdef _UNICODE
		String& operator = (const char* str);
		String& operator += (const char* str);
		String& append(const char* str);
#else
		String& operator = (const wchar_t* str);
		String& operator += (const wchar_t* str);
		String& append(const wchar_t * str);
#endif
		String& operator += (tchar c);
		String& operator +=(int v);
		String& operator +=(unsigned int v);
		String& operator +=(__int64 v);
		String& operator +=(unsigned __int64 v);
		String& operator +=(short v);
		String& operator +=(unsigned short v);
		String& operator +=(long v);
		String& operator +=(unsigned long v);
		String& operator +=(float v);
		String& operator +=(double v);
		String& operator +=(long double v);
		String& operator +=(const tchar* v);

		friend StringPtr operator +(int v, const String& str);
		friend StringPtr operator +(unsigned int v, const String& str);
		friend StringPtr operator +(__int64 v, const String& str);
		friend StringPtr operator +(unsigned __int64 v, const String& str);
		friend StringPtr operator +(short v, const String& str);
		friend StringPtr operator +(unsigned short v, const String& str);
		friend StringPtr operator +(long v, const String& str);
		friend StringPtr operator +(unsigned long v, const String& str);
		friend StringPtr operator +(float v, const String& str);
		friend StringPtr operator +(double v, const String& str);
		friend StringPtr operator +(long double v, const String& str);
		friend StringPtr operator +(tchar v, const String& str);
		friend StringPtr operator +(const tchar* v, const String& str);
		friend StringPtr operator +(const String& v, const String& str);

		friend StringPtr operator +(const String& str, int v);
		friend StringPtr operator +(const String& str, unsigned int v);
		friend StringPtr operator +(const String& str, __int64 v);
		friend StringPtr operator +(const String& str, unsigned __int64 v);
		friend StringPtr operator +(const String& str, short v);
		friend StringPtr operator +(const String& str, unsigned short v);
		friend StringPtr operator +(const String& str, long v);
		friend StringPtr operator +(const String& str, unsigned long v);
		friend StringPtr operator +(const String& str, float v);
		friend StringPtr operator +(const String& str, double v);
		friend StringPtr operator +(const String& str, long double v);
		friend StringPtr operator +(const String& str, tchar v);
		friend StringPtr operator +(const String& str, const tchar* v);



		String& append(tchar c);
		String& append(const tchar* str);
		String& append(const tchar* str, size_t size);
		String& append(const String& str);
		String& append(int v);
		String& append(unsigned int v);
		String& append(__int64 v);
		String& append(unsigned __int64 v);
		String& append(short v);
		String& append(unsigned short v);
		String& append(long v);
		String& append(unsigned long v);
		String& append(float v);
		String& append(double v);
		String& append(long double v);
		bool equals(const tchar* str) const;
		bool equals(const String& str) const;
		bool equalsIgnoreCase(const tchar* str) const;
		bool equalsIgnoreCase(const String& str) const;

		int compare(const tchar* str) const;
		int compare(const String& str) const;
		int compareIgnoreCase(const tchar* str) const;
		int compareIgnoreCase(const String& str) const;


		bool operator==(const tchar* str) const;
		bool operator==(const String& str) const;
		friend bool operator==(const tchar* str, const String& str2);

		String& format(const tchar* fmat, ...);
		size_t getCapacity() const;
		size_t getSize() const;
		operator const tchar*() const;
		const tchar* getData() const;
		tchar& operator [](size_t index) const;

		static const size_t npos = -1;

		size_t find(tchar c, size_t start = 0) const;
		size_t rfind(tchar c, size_t start) const;
		size_t rfind(tchar c) const;
		StringPtr trim();
		StringPtr trimLeft();
		StringPtr trimRight();

#ifdef _UNICODE
		friend std::wostream& operator<<(std::wostream& os, const String& dt); 
#else
		friend std::ostream& operator<<(std::ostream& os, const String& dt);
#endif

	private:
		void assign(const tchar* buf, size_t size);
		tchar* alloc(size_t size);
	private:
		size_t mCapacity;
		size_t mSize;
		tchar* mData;
	};
}


