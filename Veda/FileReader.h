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
	class VEDA_EXPORT WFileReader : public FileReadBase<wchar_t>
	{
	public:
		WFileReader(const char* file, FileEncoding enc = FileEncoding::ASCII);
		WFileReader(const wchar_t* file, FileEncoding enc = FileEncoding::ASCII);
		WFileReader(const char* file, bool detectEnc);
		WFileReader(const wchar_t* file, bool detectEnc);
		virtual ~WFileReader(){};

		void close();
	private:
		void InitFileInternal(bool detectEnc);
	protected:
		std::ifstream mAFile;
		std::wifstream mUFile;
		bool mIsUFile;
	};


	
	// not thread safe
	class VEDA_EXPORT CFileReader : public FileReadBase<char>
	{
	public:
		CFileReader(const char* file, FileEncoding enc = FileEncoding::ASCII);
		CFileReader(const wchar_t* file, FileEncoding enc = FileEncoding::ASCII);
		CFileReader(const char* file, bool detectEnc);
		CFileReader(const wchar_t* file, bool detectEnc);
		virtual ~CFileReader(){};

		void close();
	private:
		void InitFileInternal(bool detectEnc);
	protected:
		std::ifstream mAFile;
		std::wifstream mUFile;
		bool mIsUFile;
	};
}