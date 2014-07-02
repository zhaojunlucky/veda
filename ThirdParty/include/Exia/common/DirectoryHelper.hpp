#pragma once
#include "Iterator.hpp"
#include <windows.h>
#include <memory>

using namespace al;
namespace eio
{
	struct FileInfo
	{

	};

	enum FileViewMode
	{
		Files,
		Dirs,
		All
	};
	class DirectoryHelperIterator : public Iterator<FileInfo*>
	{
	public:
		virtual bool hasNext()
		{
			return checkHasNextFile();
		}
		virtual FileInfo* get()
		{

		}

		virtual ~DirectoryHelperIterator()
		{
			
		}
	private:
		friend class DirectoryHelper;
		DirectoryHelperIterator(HANDLE h, FileViewMode m)
			:mFileHandle(h), mFileViewMode(m), mHasMoreFiles(true)
		{
		}

		bool checkHasNextFile()
		{
			if (mFileHandle != INVALID_HANDLE_VALUE && mHasMoreFiles)
			{

			}
		}
	private:
		HANDLE mFileHandle;
		FileViewMode mFileViewMode;
		bool mHasMoreFiles;
		FileInfo mFileInfo;
		
	};

	class DirectoryHelper
	{
	public:
		DirectoryHelper()
		{

		}
		~DirectoryHelper()
		{

		}

		
	};
}