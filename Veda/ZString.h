#pragma once

#include <stdarg.h>
#include <string.h>
#include <Array.h>
#include <utility>
#include <iostream>
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

#define cmpstr wcscmp
#define cmpicase wcsicmp
#define copy wcscpy
#define len wcslen
#define cat wcscat
#define _vsntprintf     _vsnwprintf
#else

#ifndef tchar
	typedef char  tchar;
#endif

#ifndef _T
#define _T(x) x
#endif

#define cmp strcmp
#define cmpicase stricmp
#define copy strcpy
#define len strlen
#define cat strcat
#define _vsntprintf     _vsnprintf

#endif

#define DEFAULT_SIZE 64
	class String
	{
	public:
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

		friend String& operator +(int v, const String& str);
		friend String& operator +(unsigned int v, const String& str);
		friend String& operator +(__int64 v, const String& str);
		friend String& operator +(unsigned __int64 v, const String& str);
		friend String& operator +(short v, const String& str);
		friend String& operator +(unsigned short v, const String& str);
		friend String& operator +(long v, const String& str);
		friend String& operator +(unsigned long v, const String& str);
		friend String& operator +(float v, const String& str);
		friend String& operator +(double v, const String& str);
		friend String& operator +(long double v, const String& str);
		friend String& operator +(tchar v, const String& str);
		friend String& operator +(const tchar* v, const String& str);
		friend String& operator +(const String& v, const String& str);

		friend String& operator +(const String& str, int v);
		friend String& operator +(const String& str, unsigned int v);
		friend String& operator +(const String& str, __int64 v);
		friend String& operator +(const String& str, unsigned __int64 v);
		friend String& operator +(const String& str, short v);
		friend String& operator +(const String& str, unsigned short v);
		friend String& operator +(const String& str, long v);
		friend String& operator +(const String& str, unsigned long v);
		friend String& operator +(const String& str, float v);
		friend String& operator +(const String& str, double v);
		friend String& operator +(const String& str, long double v);
		friend String& operator +(const String& str, tchar v);
		friend String& operator +(const String& str, const tchar* v);



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
		tchar& operator [](size_t index) const;

#ifdef _UNICODE
		friend std::wostream& operator<<(std::wostream& os, const String& dt); 
#else
		friend std::ostream& operator<<(std::ostream& os, const String& dt);
#endif

	private:
		bool isDefaultBuffer() const;
		void assign(const tchar* buf, size_t size);
	private:
		size_t mCapacity;
		size_t mSize;
		tchar mBuf[DEFAULT_SIZE];
		tchar* mData;
	};


}


