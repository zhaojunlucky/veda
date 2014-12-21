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
		if (_waccess(file, 0) != -1)
		{
			DWORD ret = GetFileAttributes(file);
			if (ret == INVALID_FILE_ATTRIBUTES)
			{
				// log error
				throw BaseException(ErrorUtil::getErrorMessage(GetLastError())->getData());
			}
			else
			{
				return (ret & FILE_ATTRIBUTE_NORMAL);
			}
		}
		else
		{
			return false;
		}
	}
	bool FileUtil::directoryExists(const wchar_t* file)
	{
		if (_waccess(file, 0) != -1)
		{
			DWORD ret = GetFileAttributes(file);
			if (ret == INVALID_FILE_ATTRIBUTES)
			{
				// log error
				throw BaseException(ErrorUtil::getErrorMessage(GetLastError())->getData());
			}
			else
			{
				return (ret & FILE_ATTRIBUTE_DIRECTORY);
			}
		}
		else
		{
			return false;
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
		// _fullpath( full, partialPath, _MAX_PATH ) != NULL
		String str = path;
		if (str.getSize() == 4 && str[1] == L':')
		{
			return; 
		}
		Vector<StringPtr> parentDirs;
		for (size_t i = 4; i < str.getSize(); i++)
		{
			auto c = str[i];
			if (c == L'\\' || c == L'/')
			{
				parentDirs.add(str.subString(0, i));
			}
		}
		// create parent directory first
		for (auto& dir : parentDirs)
		{
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
		String path = exeFullPath;
		return path.subString(0,path.rfind(L'\\'));
	}

	StringPtr FileUtil::getSpecialFolderPath(REFKNOWNFOLDERID sf)
	{
		wchar_t* dirPath = NULL;
		auto hr = SHGetKnownFolderPath(sf, 0, NULL, &dirPath);
		if (hr == S_OK)
		{
			auto path = makeStringPtr(dirPath);
			CoTaskMemFree(dirPath);
			return path;
		}
		else
		{
			// log error
			throw BaseException(L"fail to get folder!");
		}
	}
}