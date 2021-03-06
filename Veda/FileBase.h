#pragma once
#ifdef _WIN32
#include <Windows.h>
#endif
#include <stdio.h>
#include "ZString.h"

namespace veda
{
#ifdef _WIN32
#define _CRT_SECURE_NO_DEPRECATE 
#endif
	enum FileEncoding
	{
		ASCII,
		UTF8,
		UNICODE_, // UTF-16
		UTF16L = UNICODE_
	};

	static FileEncoding _DetectEncoding(const char header[3])
	{
		FileEncoding enc = FileEncoding::ASCII;
		if (header[0] == 0xFF && header[1] == 0xFE)
		{
			enc = FileEncoding::UNICODE_;
		}
		else if (header[0] == 0xEF && header[1] == 0xBB && header[2] == 0xBF)
		{
			enc = FileEncoding::UTF8;
		}

		return enc;
	}

	static FileEncoding DetectEncoding(const wchar_t* file)
	{
		char buf[3];
		memset(buf, 0, sizeof(char)* 3);
		FILE* fp = 0;
		errno_t err = _wfopen_s(&fp, file, L"r");
		wchar_t buffer[100];
		_wcserror_s(buffer, 80,err);
		if (fp)
		{
			fread(buf, sizeof(char), 3, fp);
			fclose(fp);
		}
		return _DetectEncoding(buf);
	}



	template<class T>
	class VEDA_EXPORT FileReadBase
	{
	public:
		FileReadBase(const char* file, FileEncoding enc)
			: mEnc(enc)
		{
			mFile.from(file);
		}
		FileReadBase(const wchar_t* file, FileEncoding enc)
			:mFile(file), mEnc(enc)
		{
			
		}
		~FileReadBase()
		{

		}

		FileEncoding GetEncoding(){ return mEnc; };
		const char* GetFilePath(){ return mFile.c_str(); };
		virtual void close() = 0;
	protected:
		String mFile;
		FileEncoding mEnc;
	};


	template<class T>
	class VEDA_EXPORT FileWriteBase
	{
	public:
		FileWriteBase(const char* file, FileEncoding enc)
			:mEnc(enc)
		{
			mFile.from(file);
		}
		FileWriteBase(const wchar_t* file, FileEncoding enc)
			:mFile(file), mEnc(enc)
		{
			
		}

		virtual void close() = 0;
		//virtual size_t Write(const T* buffer, size_t size);
		//virtual size_t WriteLine(const T* buffer, size_t size);
		FileEncoding GetEncoding(){ return mEnc; };
		const char* GetFilePath(){ return mFile.c_str(); };
	protected:
		String mFile;
		FileEncoding mEnc;
	};
}