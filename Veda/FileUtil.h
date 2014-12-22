#pragma once
#include <Windows.h>
#include "SpecialFolder.h"
#include "ZString.h"
#include "veda.h"
namespace veda
{

	
	class VEDA_EXPORT FileUtil
	{
	public:
		FileUtil();
		~FileUtil();
		static bool fileExists(const wchar_t* file);
		static bool directoryExists(const wchar_t* file);
		static void deleteFile(const wchar_t* file);
		static void createDirectory(const wchar_t* path);
		static void createDirectoryRecursive(const wchar_t* path);
		// doesn't contain backslash at the end
		static StringPtr getCurrentExeDir();
		// doesn't contain backslash at the end
		static StringPtr getSpecialFolderPath(REFKNOWNFOLDERID sf);
		static StringPtr getFileFullPath(const wchar_t* partialPath);
	};

}

