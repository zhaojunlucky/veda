#include "stdafx.h"
#include "StringConvert.h"

namespace veda
{
	StringConvert::StringConvert()
	{
	}


	StringConvert::~StringConvert()
	{
	}

	const wchar_t* StringConvert::char2wchar(const char* str, size_t size)
	{
		int cchStr = MultiByteToWideChar(::GetACP(), 0, str, size, NULL, 0) + 1;
		wchars.reserve(cchStr);
		::MultiByteToWideChar(::GetACP(), 0, str, size, &wchars[0], cchStr);
		return &wchars[0];
	}
	const wchar_t* StringConvert::char2wchar(const char* str)
	{
		int cchStr = MultiByteToWideChar(::GetACP(), 0, str, -1, NULL, 0) + 1;
		wchars.reserve(cchStr);
		::MultiByteToWideChar(::GetACP(), 0, str, -1, &wchars[0], cchStr);
		return &wchars[0];
	}
	const char* StringConvert::wchar2char(const wchar_t* str,size_t size)
	{
		int cchStr = WideCharToMultiByte(::GetACP(), 0, str, size, NULL, 0, NULL, NULL) + 1;
		chars.reserve(cchStr);
		WideCharToMultiByte(::GetACP(), 0, str, size, &chars[0], cchStr, NULL, NULL);
		return &chars[0];
	}
	const char* StringConvert::wchar2char(const wchar_t* str)
	{
		int cchStr = WideCharToMultiByte(::GetACP(), 0, str, -1, NULL, 0, NULL, NULL)+1;
		chars.reserve(cchStr);
		WideCharToMultiByte(::GetACP(), 0, str, -1, &chars[0], cchStr, NULL, NULL);
		return &chars[0];
	}
}
