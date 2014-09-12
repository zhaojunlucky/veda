#pragma once
#include <string>
#include "FileReader.h"


using namespace std;
namespace eio
{
	class WBufferedFileReader : public WFileReader
	{
	public:
		WBufferedFileReader(const char* file, FileEncoding enc = FileEncoding::ASCII)
			:WFileReader(file, enc)
		{

		}
		WBufferedFileReader(const wchar_t* file, FileEncoding enc = FileEncoding::ASCII)
			:WFileReader(file, enc)
		{

		}
		WBufferedFileReader(const char* file, bool detectEnc)
			:WFileReader(file, detectEnc)
		{

		}
		WBufferedFileReader(const wchar_t* file, bool detectEnc)
			:WFileReader(file, detectEnc)
		{

		}

		const wchar_t* ReadLine()
		{
			mULineBuffer.clear();

			if (mIsUFile)
			{
				if (mUFile.eof())
				{
					return NULL;
				}
				getline(mUFile, mULineBuffer);
			}
			else
			{
				if (mAFile.eof())
				{
					return NULL;
				}
				mALineBuffer.clear();
				getline(mAFile, mALineBuffer);
				mULineBuffer = mSci.Char2Wchar(mALineBuffer.c_str(), mALineBuffer.size());
			}
			return mULineBuffer.c_str();
		}
	private:
		string mALineBuffer;
		wstring mULineBuffer;
	};

	class CBufferedFileReader : public CFileReader
	{
	public:
		CBufferedFileReader(const char* file, FileEncoding enc = FileEncoding::ASCII)
			:CFileReader(file, enc)
		{

		}
		CBufferedFileReader(const wchar_t* file, FileEncoding enc = FileEncoding::ASCII)
			:CFileReader(file, enc)
		{

		}
		CBufferedFileReader(const char* file, bool detectEnc)
			:CFileReader(file, detectEnc)
		{

		}
		CBufferedFileReader(const wchar_t* file, bool detectEnc)
			:CFileReader(file, detectEnc)
		{

		}

		const char* ReadLine()
		{
			mALineBuffer.clear();

			if (!mIsUFile)
			{
				if (mAFile.eof())
				{
					return NULL;
				}
				getline(mAFile, mALineBuffer);
			}
			else
			{
				if (mUFile.eof())
				{
					return NULL;
				}
				mULineBuffer.clear();
				getline(mUFile, mULineBuffer);
				mALineBuffer = mSci.Wchar2Char(mULineBuffer.c_str(), mULineBuffer.size());
			}
			return mALineBuffer.c_str();
		}
	private:
		std::string mALineBuffer;
		std::wstring mULineBuffer;
	};
}