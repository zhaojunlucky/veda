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
	class WFileWriter : public FileWriteBase < wchar_t >
	{
	public:
		VEDA_EXPORT WFileWriter(const char* file, FileEncoding enc = FileEncoding::ASCII)
			:FileWriteBase<wchar_t>(file, enc)
		{
			InitFileInternal();
		}
		VEDA_EXPORT WFileWriter(const wchar_t* file, FileEncoding enc = FileEncoding::ASCII)
			:FileWriteBase<wchar_t>(file, enc)
		{
			InitFileInternal();
		}



		VEDA_EXPORT size_t Write(const wchar_t* buffer, size_t size)
		{
			if (mIsUFile)
			{
				mUFile << buffer;
			}
			else
			{
				AString tmp;
				tmp.from(buffer, size);
				mAFile << tmp;
			}
			return 0;
		}
		VEDA_EXPORT size_t WriteLine(const wchar_t* buffer, size_t size)
		{
			if (mIsUFile)
			{
				mUFile << buffer << L"\n";
			}
			else
			{
				AString tmp;
				tmp.from(buffer, size);
				mAFile << tmp << "\n";
			}
			return 0;
		}

		VEDA_EXPORT void close()
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
	};

	class CFileWriter : public FileWriteBase < char >
	{
	public:
		VEDA_EXPORT CFileWriter(const char* file, FileEncoding enc)
			:FileWriteBase<char>(file, enc)
		{
			InitFileInternal();
		}
		VEDA_EXPORT CFileWriter(const wchar_t* file, FileEncoding enc)
			:FileWriteBase<char>(file, enc)
		{
			InitFileInternal();
		}


		VEDA_EXPORT size_t Write(const char* buffer, size_t size)
		{
			if (mIsUFile)
			{
				WString tmp;
				tmp.from(buffer, size);
			}
			else
			{
				mAFile << buffer;
			}
			return 0;
		}
		VEDA_EXPORT size_t WriteLine(const char* buffer, size_t size)
		{
			if (mIsUFile)
			{
				WString tmp;
				tmp.from(buffer, size);
				mUFile << tmp << L"\n";
			}
			else
			{
				mAFile << buffer << "\n";
			}
			return 0;
		}

		VEDA_EXPORT void close()
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
	};
}
