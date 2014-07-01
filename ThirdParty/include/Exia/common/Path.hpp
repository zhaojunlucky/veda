#pragma once
#include <Windows.h>
#include <string>

namespace eio
{
	class Path
	{
	public:
		static bool getModulePath(HMODULE hmodule,std::wstring& path)
		{
			wchar_t buf[512];
			if (GetModuleFileName(hmodule, buf, 512))
			{
				path = buf;
				path = path.substr(0, path.rfind(L'\\'));
				return true;
			}
			return false;
		}
	};
}