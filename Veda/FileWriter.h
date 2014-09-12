#pragma once

#include "FileBase.h"
#include <fstream>
#include <string>
#include "StringConvert.h"
#include <locale>
#include <codecvt>
#include <memory>

namespace veda
{
	using namespace ::std;
	class WFileWriter : public FileWriteBase<wchar_t>
	{
	public:
		WFileWriter(const char* file, FileEncoding enc = FileEncoding::ASCII)
			:FileWriteBase<wchar_t>(file, enc)
		{
				InitFileInternal();
			}
		WFileWriter(const wchar_t* file, FileEncoding enc = FileEncoding::ASCII)
			:FileWriteBase<wchar_t>(file, enc)
		{
				InitFileInternal();
			}

		

		size_t Write(const wchar_t* buffer, size_t size)
		{
			if (mIsUFile)
			{
				mUFile << buffer;
			}
			else
			{
				string tmp = mSci.wchar2char(buffer, size);
				mAFile << tmp;
			}
			return 0;
		}
		size_t WriteLine(const wchar_t* buffer, size_t size)
		{
			if (mIsUFile)
			{
				mUFile << buffer << L"\n";
			}
			else
			{
				string tmp = mSci.wchar2char(buffer, size);
				mAFile << tmp << "\n";
			}
			return 0;
		}

		void close()
		{
			if (mIsUFile)
			{
				mUFile.close();
			}
			else
			{
				mAFile.close();
			}
		}

	private:
		void InitFileInternal()
		{

			if (mEnc == FileEncoding::ASCII)
			{
				mIsUFile = false;
				mAFile.open(mFile.c_str());
			}
			else if (mEnc == FileEncoding::UTF8)
			{
				mIsUFile = true;
				mUFile.open(mFile.c_str());
#ifdef _WIN32				
				mUFile.imbue(locale(locale::classic(), new ::std::codecvt_utf8<wchar_t>));
#else
				mUFile.imbue(std::locale("en_US.UTF-8"));
#endif
			}
			else
			{
				mIsUFile = true;
				mUFile.open(mFile);
#ifdef _WIN32
				mUFile.imbue(locale(locale::classic(), new codecvt_utf16<wchar_t>));
#else
				mUFile.imbue(std::locale("en_US.UTF-8"));
#endif
			}
		}
	protected:
		ofstream mAFile;
		wofstream mUFile;
		bool mIsUFile;
		StringConvert mSci;
	};

	class CFileWriter : public FileWriteBase<char>
	{
	public:
		CFileWriter(const char* file, FileEncoding enc)
			:FileWriteBase<char>(file, enc)
		{
				InitFileInternal();
			}
		CFileWriter(const wchar_t* file, FileEncoding enc)
			:FileWriteBase<char>(file, enc)
		{
				InitFileInternal();
			}


		size_t Write(const char* buffer, size_t size)
		{
			if (mIsUFile)
			{
				wstring tmp = mSci.char2wchar(buffer, size);
				mUFile << tmp;
			}
			else
			{
				mAFile << buffer;
			}
			return 0;
		}
		size_t WriteLine(const char* buffer, size_t size)
		{
			if (mIsUFile)
			{
				wstring tmp = mSci.char2wchar(buffer, size);
				mUFile << tmp << L"\n";
			}
			else
			{
				mAFile << buffer << "\n";
			}
			return 0;
		}

		void close()
		{
			if (mIsUFile)
			{
				mUFile.close();
			}
			else
			{
				mAFile.close();
			}
		}

	private:
		void InitFileInternal()
		{

			if (mEnc == FileEncoding::ASCII)
			{
				mIsUFile = false;
				mAFile.open(mFile.c_str());
			}
			else if (mEnc == FileEncoding::UTF8)
			{
				mIsUFile = true;
				mUFile.open(mFile.c_str());
#ifdef _WIN32				
				mUFile.imbue(locale(locale::classic(), new ::std::codecvt_utf8<wchar_t>));
#else
				mUFile.imbue(std::locale("en_US.UTF-8"));
#endif
			}
			else
			{
				mIsUFile = true;
				mUFile.open(mFile);
#ifdef _WIN32
				mUFile.imbue(locale(locale::classic(), new codecvt_utf16<wchar_t>));
#else
				mUFile.imbue(std::locale("en_US.UTF-8"));
#endif
			}
		}
	protected:
		ofstream mAFile;
		wofstream mUFile;
		bool mIsUFile;
		StringConvert mSci;
	};
}
