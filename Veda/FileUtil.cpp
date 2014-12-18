#include "stdafx.h"
#include "FileUtil.h"

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
		return (GetFileAttributes(file) == FILE_ATTRIBUTE_NORMAL);
	}
	bool FileUtil::directoryExists(const wchar_t* file)
	{
		return (GetFileAttributes(file) == FILE_ATTRIBUTE_DIRECTORY);
	}
	void FileUtil::deleteFile(const wchar_t* file)
	{
		DeleteFile(file);
	}
}