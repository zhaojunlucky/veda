#pragma once
#include <tchar.h>
#include <Array.h>
#include <memory>
#include <stdarg.h>
namespace veda
{
	class StringHelper
	{
	public:
		StringHelper(TCHAR* buf, size_t max);
		~StringHelper();
		operator TCHAR*();
		TCHAR* get();
		StringHelper& operator=(int v);
		StringHelper& operator=(__int64 v);
		StringHelper& operator=(float v);
		StringHelper& operator=(double v);
		StringHelper& operator=(short v);
		StringHelper& operator=(char v);
		StringHelper& operator=(unsigned int v);
		StringHelper& operator=(unsigned __int64 v);
		StringHelper& operator=(unsigned short v);
		StringHelper& operator=(unsigned char v);
		StringHelper& operator=(bool v);
		StringHelper& operator=(long v);
		StringHelper& operator=(unsigned long v);
		StringHelper& operator=(long double v);
		StringHelper& operator=(const TCHAR* str);
		
		StringHelper& operator+=(int v);
		StringHelper& operator+=(__int64 v);
		StringHelper& operator+=(float v);
		StringHelper& operator+=(double v);
		StringHelper& operator+=(short v);
		StringHelper& operator+=(char v);
		StringHelper& operator+=(unsigned int v);
		StringHelper& operator+=(unsigned __int64 v);
		StringHelper& operator+=(unsigned short v);
		StringHelper& operator+=(unsigned char v);
		StringHelper& operator+=(bool v);
		StringHelper& operator+=(long v);
		StringHelper& operator+=(unsigned long v);
		StringHelper& operator+=(long double v);
		StringHelper& operator+=(const TCHAR* str);

		StringHelper& format(const TCHAR* str, ...);
	private:
		void formatTemp(const TCHAR* str,...);
	private:
		TCHAR* buf;
		std::shared_ptr<Array<TCHAR>> mBuf;
	};
}


