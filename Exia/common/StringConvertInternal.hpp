#pragma once
#include <Windows.h>

#include <string>

namespace eio
{
	// thread safe
	__declspec(thread) class StringConvertInternal
	{
	public:
		StringConvertInternal()
		{

		}
		~StringConvertInternal()
		{

		}

		const char* Wchar2Char(const wchar_t* src, size_t len)
		{
			size_t n = WideCharToMultiByte(0, // specify the code page used to perform the conversion
				0,         // no special flags to handle unmapped characters
				src,     // wide character string to convert
				len,   // the number of wide characters in that string
				NULL,      // no output buffer given, we just want to know how long it needs to be
				0,
				NULL,      // no replacement character given
				NULL);    // we don't want to know if a character didn't make it through the translation

			// make sure the buffer is big enough for this, making it larger if necessary
			char* buf = new char[n + 1];

			WideCharToMultiByte(0, // specify the code page used to perform the conversion

				0,         // no special flags to handle unmapped characters

				src,   // wide character string to convert

				len,   // the number of wide characters in that string

				buf, // put the output ascii characters at the end of the buffer

				n,                           // there is at least this much space there

				NULL,      // no replacement character given

				NULL);
			buf[n] = '\0';
			mCharStr = buf;
			delete buf;
			return mCharStr.c_str();
		}
		const wchar_t* Char2Wchar(const char* src, size_t len)
		{
			size_t n = MultiByteToWideChar(CP_ACP, 0, src, len, NULL, 0);
			wchar_t* buf = new wchar_t[n + 1];

			MultiByteToWideChar(CP_ACP, 0, src, len, buf, n);
			buf[n] = L'\0';
			mWcharStr = buf;
			delete buf;
			return mWcharStr.c_str();
		}

	private:
		std::string mCharStr;
		std::wstring mWcharStr;
	};
}

	

