#pragma once
#include "FileBase.h"
#include <fstream>
#include <string>
#include <locale>
#include <codecvt>


namespace veda
{
	using namespace std;

	// not thread safe
	class  WFileReader : public FileReadBase<wchar_t>
	{
	public:
		VEDA_EXPORT WFileReader(const char* file, FileEncoding enc = FileEncoding::ASCII);
		VEDA_EXPORT WFileReader(const wchar_t* file, FileEncoding enc = FileEncoding::ASCII);
		VEDA_EXPORT WFileReader(const char* file, bool detectEnc);
		VEDA_EXPORT WFileReader(const wchar_t* file, bool detectEnc);
		VEDA_EXPORT virtual ~WFileReader(){};

		VEDA_EXPORT void close();
	private:
		void InitFileInternal(bool detectEnc);
	protected:
		std::ifstream mAFile;
		std::wifstream mUFile;
		bool mIsUFile;
	};


	
	// not thread safe
	class CFileReader : public FileReadBase<char>
	{
	public:
		VEDA_EXPORT CFileReader(const char* file, FileEncoding enc = FileEncoding::ASCII);
		VEDA_EXPORT CFileReader(const wchar_t* file, FileEncoding enc = FileEncoding::ASCII);
		VEDA_EXPORT CFileReader(const char* file, bool detectEnc);
		VEDA_EXPORT CFileReader(const wchar_t* file, bool detectEnc);
		VEDA_EXPORT virtual ~CFileReader(){};

		VEDA_EXPORT void close();
	private:
		void InitFileInternal(bool detectEnc);
	protected:
		std::ifstream mAFile;
		std::wifstream mUFile;
		bool mIsUFile;
	};
}