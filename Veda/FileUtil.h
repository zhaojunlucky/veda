#pragma once
#include <Windows.h>
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
	};

}

