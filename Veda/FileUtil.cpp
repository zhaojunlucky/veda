#include "stdafx.h"
#include "FileUtil.h"
#include "BaseException.h"
#include "ErrorUtil.h"
#include "Queue.h"
namespace veda
{
	FileUtil::FileUtil()
	{
	}


	FileUtil::~FileUtil()
	{
	}

	bool FileUtil::fileExists(const wchar_t* file)
	{
		DWORD ret = GetFileAttributes(file);
		if (ret == INVALID_FILE_ATTRIBUTES)
		{
			// log error
			throw BaseException(ErrorUtil::getErrorMessage(GetLastError())->getData());
		}
		else
		{
			return (ret == FILE_ATTRIBUTE_NORMAL);
		}
	}
	bool FileUtil::directoryExists(const wchar_t* file)
	{
		DWORD ret = GetFileAttributes(file);
		if (ret == INVALID_FILE_ATTRIBUTES)
		{
			// log error
			throw BaseException(ErrorUtil::getErrorMessage(GetLastError())->getData());
		}
		else
		{
			return (ret == FILE_ATTRIBUTE_DIRECTORY);
		}
	}
	void FileUtil::deleteFile(const wchar_t* file)
	{
		if (!DeleteFile(file))
		{
			// log error
			throw BaseException(ErrorUtil::getErrorMessage(GetLastError())->getData());
		}
	}

	void FileUtil::createDirectory(const wchar_t* path)
	{
		if (NULL == path)
		{
			// log error
			throw BaseException(L"parameter error, path is null.");
		}
		if (!CreateDirectory(path, NULL))
		{
			DWORD lastError = GetLastError();
			if (ERROR_ALREADY_EXISTS != lastError)
			{
				// log error
				throw BaseException(ErrorUtil::getErrorMessage(GetLastError())->getData());
			}
		}

	}

	void FileUtil::createDirectoryRecursive(const wchar_t* path)
	{
		String str = path;
		if (str.getSize() == 2 && str[1] == L':')
		{
			return; 
		}
		LinkListQueue<StringPtr> parentDirs;
		for (size_t i = 2; i < str.getSize(); i++)
		{
			auto c = str[i];
			if (c == L'\\' || c == L'/')
			{
				parentDirs.enqueue(str.subString(0, i));
			}
		}
		// create parent directory first
		while (!parentDirs.isEmpty())
		{
			auto& dir = parentDirs.dequeue();
			if (!directoryExists(dir->getData()))
			{
				createDirectory(dir->getData());
			}
		}
		// create itself
		if (!directoryExists(path))
		{
			createDirectory(path);
		}
	}

	StringPtr FileUtil::getCurrentExeDir()
	{
		wchar_t exeFullPath[MAX_PATH];
		GetModuleFileName(NULL, exeFullPath, MAX_PATH);
		return makeStringPtr(exeFullPath);
	}

	StringPtr FileUtil::getSpecialFolderPath(SpecialFolder sf)
	{
		wchar_t  dirPath[MAX_PATH];
		SHGetFolderPath(NULL, sf, NULL, 0, dirPath);
		return makeStringPtr(dirPath);
	}
}