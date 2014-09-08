#include "stdafx.h"
#include "Directory.h"

namespace veda
{
	DirectoryIterator::~DirectoryIterator()
	{
		if (mHandle != INVALID_HANDLE_VALUE)
		{
			FindClose(mHandle);
		}
	}
	DirectoryIterator::DirectoryIterator(const wchar_t* dirPath, FileSearchMode mode)
		: mSearchMode(mode)
	{
		mDirPath = mPathUtil.trimPathRightSeparator(dirPath);
		wstring find = mPathUtil.combinePath(mDirPath.c_str(), L"*.*");
		mHandle = FindFirstFile(find.c_str(), &mWFD);
		mHasNext = processNextFile();
	}

	DirectoryIterator::DirectoryIterator(const wchar_t* dirPath, const wchar_t* extension)
		: mSearchMode(FileSearchMode::Files), mExtension(extension)
	{
		mDirPath = mPathUtil.trimPathRightSeparator(dirPath);
		wstring find = mPathUtil.combinePath(mDirPath.c_str(), extension);
		mHandle = FindFirstFile(find.c_str(), &mWFD);
		mHasNext = processNextFile();
	}


	bool DirectoryIterator::hasNext() const
	{
		return mHasNext;
	}
	const FileInfo & DirectoryIterator::get()
	{
		mFileInfo.fileName = mWFD.cFileName;
		mFileInfo.fullPath = mPathUtil.combinePath(mDirPath.c_str(), mWFD.cFileName, 0);
		mFileInfo.isDirectory = ((mWFD.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 1);
		return mFileInfo;
	}

	bool DirectoryIterator::processNextFile()
	{
		bool has = false;
		if (mHandle != INVALID_HANDLE_VALUE)
		{
			do
			{
				// is directory
				if ((mWFD.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) &&
					(mSearchMode == FileSearchMode::Files || (wcscmp(mWFD.cFileName, L".") || wcscmp(mWFD.cFileName, L".."))))
				{
					continue;
				}
				else
				{
					has = true;
					break;
				}
				// if file
				if (mSearchMode != FileSearchMode::Files)
				{
					continue;
				}
				else
				{
					has = true;
					break;
				}

			} while (FindNextFile(mHandle, &mWFD));
		}
		return has;
	}


	Directory::Directory(const wchar_t* dirPath)
		:mDirPath(dirPath)
	{
		mIsExist = (GetFileAttributes(dirPath) == FILE_ATTRIBUTE_DIRECTORY);
	}


	Directory::~Directory()
	{
	}

	bool Directory::isExists() const
	{
		return mIsExist;
	}
	DirectoryIteratorPtr Directory::searchFiles(const wchar_t* extension)
	{
		if (!mIsExist)
		{
			throw "directory is not exists";
		}
		shared_ptr<DirectoryIterator> p(new DirectoryIterator(mDirPath.c_str(), extension));
		return std::move(p);
	}
	DirectoryIteratorPtr Directory::searchDirectories()
	{
		if (!mIsExist)
		{
			throw "directory is not exists";
		}
		shared_ptr<DirectoryIterator> p(new DirectoryIterator(mDirPath.c_str(), FileSearchMode::Directories));
		return std::move(p);
	}
	DirectoryIteratorPtr Directory::searchAll()
	{
		if (!mIsExist)
		{
			throw "directory is not exists";
		}
		shared_ptr<DirectoryIterator> p(new DirectoryIterator(mDirPath.c_str(), FileSearchMode::All));
		return std::move(p);
	}
}