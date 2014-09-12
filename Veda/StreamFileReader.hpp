#pragma once
#include <string>
#include <queue>
#include "FileReader.hpp"
#include "StringConvert.h"

namespace veda
{
#define BUFFER_SIZE 4096
	template <class T>
	void Push2Queue(std::queue<T>& q, const T* data, size_t size)
	{
		for (size_t i = 0; i < size; i++)
		{
			q.push(data[i]);
		}
	}

	class WStreamFileReader : public WFileReader
	{
	public:
		WStreamFileReader(const char* file, FileEncoding enc = FileEncoding::ASCII)
			:WFileReader(file, enc)
		{

		}
		WStreamFileReader(const wchar_t* file, FileEncoding enc = FileEncoding::ASCII)
			:WFileReader(file, enc)
		{

		}
		WStreamFileReader(const char* file, bool detectEnc)
			:WFileReader(file, detectEnc)
		{

		}
		WStreamFileReader(const wchar_t* file, bool detectEnc)
			:WFileReader(file, detectEnc)
		{

		}

		size_t WStreamFileReader::Read(wchar_t* buffer, size_t bufferSize)
		{
			size_t readed = 0;
			do{
				while (!mBuffer.empty() && readed < bufferSize)
				{
					buffer[readed++] = mBuffer.front();
					mBuffer.pop();
				}
				ReadBufferQueue();
			} while (readed < bufferSize &&!Eof());
			return readed;
		}

	private:
		void ReadBufferQueue()
		{
			if (mIsUFile && !mUFile.eof())
			{
				size_t n = mUFile.readsome(mWBuffer, BUFFER_SIZE - 1);
				Push2Queue<wchar_t>(mBuffer, mWBuffer, n);
			}
			else if (!mAFile.eof())
			{
				size_t n = mAFile.readsome(mCBuffer, BUFFER_SIZE - 1);
				mCBuffer[n] = '\0';
				std::wstring tmp = mSci.char2wchar(mCBuffer, n);
				Push2Queue<wchar_t>(mBuffer, tmp.c_str(), tmp.size());
			}
		}
		bool Eof()
		{
			return ((mIsUFile && mUFile.eof()) || mAFile.eof());
		}
	private:
		std::queue<wchar_t> mBuffer;
		char mCBuffer[BUFFER_SIZE];
		wchar_t mWBuffer[BUFFER_SIZE];
	};

	class CStreamFileReader : public CFileReader
	{
	public:
		CStreamFileReader(const char* file, FileEncoding enc = FileEncoding::ASCII)
			:CFileReader(file, enc)
		{

		}
		CStreamFileReader(const wchar_t* file, FileEncoding enc = FileEncoding::ASCII)
			:CFileReader(file, enc)
		{

		}
		CStreamFileReader(const char* file, bool detectEnc)
			:CFileReader(file, detectEnc)
		{

		}
		CStreamFileReader(const wchar_t* file, bool detectEnc)
			:CFileReader(file, detectEnc)
		{

		}

		size_t CStreamFileReader::Read(wchar_t* buffer, size_t bufferSize)
		{
			size_t readed = 0;
			do{
				while (!mBuffer.empty() && readed < bufferSize)
				{
					buffer[readed++] = mBuffer.front();
					mBuffer.pop();
				}
				ReadBufferQueue();
			} while (readed < bufferSize &&!Eof());
			return readed;
		}

	private:
		void ReadBufferQueue()
		{
			if (mIsUFile && !mUFile.eof())
			{
				size_t n = mUFile.readsome(mWBuffer, BUFFER_SIZE - 1);
				mWBuffer[n] = L'\0';
				std::string tmp = mSci.wchar2char(mWBuffer, n);
				Push2Queue<char>(mBuffer, tmp.c_str(), tmp.size());
			}
			else if (!mAFile.eof())
			{
				size_t n = mAFile.readsome(mCBuffer, BUFFER_SIZE - 1);

				Push2Queue<char>(mBuffer, mCBuffer, n);
			}
		}
		bool Eof()
		{
			return ((mIsUFile && mUFile.eof()) || mAFile.eof());
		}
	private:
		std::queue<char> mBuffer;
		char mCBuffer[BUFFER_SIZE];
		wchar_t mWBuffer[BUFFER_SIZE];
	};
}
