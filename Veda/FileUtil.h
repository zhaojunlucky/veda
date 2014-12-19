#pragma once
#include <Windows.h>
#include "SpecialFolder.h"
namespace veda
{

	
	class FileUtil
	{
	public:
		FileUtil();
		~FileUtil();
		static bool fileExists(const wchar_t* file);
		static bool directoryExists(const wchar_t* file);
		static void deleteFile(const wchar_t* file);
		static void createDirectory(const wchar_t* path);
		static void createDirectoryRecursive(const wchar_t* path);
		static StringPtr getCurrentExeDir();
		static StringPtr getSpecialFolderPath(SpecialFolder sf);
	};

}

