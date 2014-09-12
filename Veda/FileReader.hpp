#pragma once
#include "FileBase.h"
#include <fstream>
#include <string>
#include <locale>
#include <codecvt>


namespace veda
{
	//using namespace std;

	// not thread safe
	class WFileReader : public FileReadBase<wchar_t>
	{
	public:
		WFileReader(const char* file, FileEncoding enc)
			:FileReadBase<wchar_t>(file, enc)
		{
				InitFileInternal(false);
		}
		WFileReader(const wchar_t* file, FileEncoding enc)
			: FileReadBase<wchar_t>(file, enc)
		{
				InitFileInternal(false);
		}
		WFileReader(const char* file, bool detectEnc)
			: FileReadBase<wchar_t>(file, FileEncoding::ASCII)

		{
				InitFileInternal(true);
		}
		WFileReader(const wchar_t* file, bool detectEnc)
			: FileReadBase<wchar_t>(file, FileEncoding::ASCII)

		{
				InitFileInternal(true);
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
		void InitFileInternal(bool detectEnc)
		{
			if (detectEnc){
				this->mEnc = DetectEncoding(mFile.c_str());
			}

			if (mEnc == FileEncoding::ASCII)
			{
				mIsUFile = false;
				mAFile.open(mFile);
			}
			else if (mEnc == FileEncoding::UTF8)
			{
				mIsUFile = true;
				mUFile.open(mFile);
#ifdef _WIN32
				mUFile.imbue(locale(locale::classic(), new codecvt_utf8<wchar_t>));
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
		std::ifstream mAFile;
		std::wifstream mUFile;
		bool mIsUFile;
		StringConvert mSci;
	};

	// not thread safe
	class CFileReader : public FileReadBase<char>
	{
	public:
		CFileReader(const char* file, FileEncoding enc)
			:FileReadBase<char>(file, enc)
		{
				InitFileInternal(false);
		}
		CFileReader(const wchar_t* file, FileEncoding enc)
			: FileReadBase<char>(file, enc)
		{
				InitFileInternal(false);
		}
		CFileReader(const char* file, bool detectEnc)
			: FileReadBase<char>(file, FileEncoding::ASCII)
		{
				InitFileInternal(true);
		}
		CFileReader(const wchar_t* file, bool detectEnc)
			: FileReadBase<char>(file, FileEncoding::ASCII)

		{
				InitFileInternal(true);
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
		void InitFileInternal(bool detectEnc)
		{
			if (detectEnc){
				this->mEnc = DetectEncoding(mFile.c_str());
			}

			if (mEnc == FileEncoding::ASCII)
			{
				mIsUFile = false;
				mAFile.open(mFile);
			}
			else if (mEnc == FileEncoding::UTF8)
			{
				mIsUFile = true;
				mUFile.open(mFile);
#ifdef _WIN32
				mUFile.imbue(locale(locale::classic(), new codecvt_utf8<wchar_t>));
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
		std::ifstream mAFile;
		std::wifstream mUFile;
		bool mIsUFile;
		StringConvert mSci;
	};

}