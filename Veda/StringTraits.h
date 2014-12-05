#pragma once
#include <Windows.h>
#include <Array.h>
#include <string.h>
#include <memory>
#include <stdarg.h>

namespace veda
{
#pragma warning(push)
#pragma warning(disable:4996)
	struct CharTraits
	{
		typedef  char value_type;
		typedef  size_t size_type;
		static const value_type* _intFormat;
		static const value_type* _uIntFormat;
		static const value_type* _lIntFormat;
		static const value_type* _floatFormat;
		static const value_type* _lFloatFormat;
		static std::shared_ptr<Array<value_type>> from(const wchar_t* str, size_type size)
		{
			int cchStr = WideCharToMultiByte(::GetACP(), 0, str, (int)size, NULL, 0, NULL, NULL) + 1;
			std::shared_ptr<Array<value_type>> p(new Array<value_type>(cchStr));
			WideCharToMultiByte(::GetACP(), 0, str, (int)size, &(*p.get())[0], cchStr, NULL, NULL);
			return p;
		}
		static std::shared_ptr<Array<value_type>> from(const wchar_t* str)
		{
			return from(str, wcslen(str));
		}
		static int _cmpstr(const value_type* str1, const value_type* str2)
		{
			return strcmp(str1, str2);
		}

		static int _cmpicase(const value_type* str1, const value_type* str2)
		{
			return stricmp(str1, str2);
		}
		static size_type _len(const value_type* str)
		{
			return strlen(str);
		}
		static bool _isSpace(value_type c)
		{
			return isspace(c)!=0;
		}
		static value_type *_copy(value_type*dest, const value_type*src)
		{
			return strcpy(dest, src);
		}
		static value_type *_ncopy(value_type*dest, const value_type*src, size_type count)
		{
			return strncpy(dest, src, count);
		}

		static value_type *_ncat(value_type*dest, const value_type*src, size_type count)
		{
			return strncat(dest, src, count);
		}

		static int format(value_type*buf, size_t len, const value_type* fmat, va_list argList)
		{
			return  _vsnprintf(buf, len, fmat, argList);
		}

		static value_type toLowercase(value_type v)
		{
			return tolower(v);
		}
		static value_type toUppercase(value_type v)
		{
			return toupper(v);
		}
	};

	struct WcharTraits
	{
		typedef wchar_t value_type;
		typedef size_t size_type;
		static const value_type* _intFormat;
		static const value_type* _uIntFormat;
		static const value_type* _lIntFormat;
		static const value_type* _floatFormat;
		static const value_type* _lFloatFormat;

		static std::shared_ptr<Array<value_type>> from(const char* str, size_type size)
		{
			int cchStr = MultiByteToWideChar(::GetACP(), 0, str, (int)size, NULL, 0) + 1;
			std::shared_ptr<Array<value_type>> p(new Array<value_type>(cchStr));
			::MultiByteToWideChar(::GetACP(), 0, str, (int)size, &(*p.get())[0], cchStr);
			return p;
		}
		static std::shared_ptr<Array<value_type>> from(const char* str)
		{
			return from(str, strlen(str));
		}
		static int _cmpstr(const wchar_t* str1, const wchar_t* str2)
		{
			return wcscmp(str1, str2);
		}
		static int _cmpicase(const value_type* str1, const value_type* str2)
		{
			return wcsicmp(str1, str2);
		}
		static size_type _len(const value_type* str)
		{
			return wcslen(str);
		}
		static bool _isSpace(value_type c)
		{
			return isspace(c)!=0;
		}
		static value_type *_copy(value_type*dest, const value_type*src)
		{
			return wcscpy(dest, src);
		}
		static value_type *_ncopy(value_type*dest, const value_type*src, size_type count)
		{
			return wcsncpy(dest, src, count);
		}
		static value_type *_ncat(value_type*dest, const value_type*src,size_type count)
		{
			return wcsncat(dest, src, count);
		}
		static int format(value_type*buf, size_t len, const value_type* fmat, va_list argList)
		{
			return   _vsnwprintf(buf, len, fmat, argList);
		}
		static value_type toLowercase(value_type v)
		{
			return towlower(v);
		}
		static value_type toUppercase(value_type v)
		{
			return towupper(v);
		}
	};


#pragma warning(pop)
}