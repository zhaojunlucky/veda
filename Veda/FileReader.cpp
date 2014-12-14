#include "stdafx.h"
#include "FileReader.h"

namespace veda
{
	WFileReader::WFileReader(const char* file, FileEncoding enc)
		:FileReadBase<wchar_t>(file, enc)
	{
		InitFileInternal(false);
	}
	WFileReader::WFileReader(const wchar_t* file, FileEncoding enc)
		: FileReadBase<wchar_t>(file, enc)
	{
		InitFileInternal(false);
	}
	WFileReader::WFileReader(const char* file, bool detectEnc)
		: FileReadBase<wchar_t>(file, FileEncoding::ASCII)

	{
		InitFileInternal(true);
	}
	WFileReader::WFileReader(const wchar_t* file, bool detectEnc)
		: FileReadBase<wchar_t>(file, FileEncoding::ASCII)

	{
		InitFileInternal(true);
	}

	void WFileReader::close()
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

	void WFileReader::InitFileInternal(bool detectEnc)
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


	CFileReader::CFileReader(const char* file, FileEncoding enc)
		:FileReadBase<char>(file, enc)
	{
		InitFileInternal(false);
	}
	CFileReader::CFileReader(const wchar_t* file, FileEncoding enc)
		: FileReadBase<char>(file, enc)
	{
		InitFileInternal(false);
	}
	CFileReader::CFileReader(const char* file, bool detectEnc)
		: FileReadBase<char>(file, FileEncoding::ASCII)
	{
		InitFileInternal(true);
	}
	CFileReader::CFileReader(const wchar_t* file, bool detectEnc)
		: FileReadBase<char>(file, FileEncoding::ASCII)

	{
		InitFileInternal(true);
	}

	void CFileReader::close()
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

	void CFileReader::InitFileInternal(bool detectEnc)
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
}