#pragma once
#include <string>
#include <io.h>
#include <direct.h>
#include <stdarg.h>
#include <Windows.h>
namespace eio
{
	class FileUtil
	{
	public:

		bool IsPathSeparator(char c) const
		{
			return c == '\\' || c == '/';
		}

		bool IsPathSeparator(wchar_t c) const
		{
			return c == L'\\' || c == L'/';
		}

		bool FileExists(const char* file) const
		{
			return access(file, 0) == 0;
		}
		bool FileExists(const wchar_t* file) const
		{
			return _waccess(file, 0) == 0;
		}
		bool DirectoryExists(const char* file) const
		{
			return FileExists(file);
		}
		bool DirectoryExists(const wchar_t* file) const
		{
			return FileExists(file);
		}
		bool CreateDirectories(const char* path, bool recursive)
		{
			if (!recursive)
			{
				return CreateDirectoryA(path) == 0;
			}
			else
			{
				std::string tmp;
				size_t i = 0;
				size_t len = strlen(path);
				while (i < len)
				{
					if (IsPathSeparator(path[i]))
					{
						if (tmp.size() > 0 && !DirectoryExists(tmp.c_str()))
						{
							if (!CreateDirectoryA(tmp.c_str()))
							{
								return false;
							}
						}
						tmp.clear();
					}
					else
					{
						tmp.push_back(path[i]);
					}

					i++;
				}
				if (tmp.size() > 0 && !DirectoryExists(tmp.c_str()))
				{
					return CreateDirectoryA(tmp.c_str());
				}
			}
		}
		bool CreateDirectories(const wchar_t* path, bool recursive) const
		{
			if (!recursive)
			{
				return CreateDirectoryW(path) == 0;
			}
			else
			{
				std::wstring tmp;
				size_t i = 0;
				size_t len = wcslen(path);
				while (i < len)
				{
					if (IsPathSeparator(path[i]))
					{
						if (tmp.size() > 0 && !DirectoryExists(tmp.c_str()))
						{
							if (!CreateDirectoryW(tmp.c_str()))
							{
								return false;
							}
						}
						tmp.clear();
					}
					else
					{
						tmp.push_back(path[i]);
					}

					i++;
				}
				if (tmp.size() > 0 && !DirectoryExists(tmp.c_str()))
				{
					return CreateDirectoryW(tmp.c_str());
				}
			}
		}
		

		// unsafe functions
		void GetCurrentWorkingDirectory(std::string* path) 
		{
			char buffer[MAX_PATH];
			getcwd(buffer, MAX_PATH);
			*path = buffer;
		}
		void GetCurrentWorkingDirectory(std::wstring* path) 
		{
			wchar_t buffer[MAX_PATH];
			GetCurrentDirectoryW(MAX_PATH, buffer);
			*path = buffer;
		}
		/*void GetUserDesktop(std::string* path)
		{

		}
		void GetUserDesktop(std::wstring* path)
		{

		}*/
		void CombinePath(std::string* dist, const char* basePath, const char* path1, ...)
		{
			CopyChars(dist, basePath, false);
			va_list argp;
			va_start(argp, path1);
			while (path1)
			{
				dist->push_back('/');
				path1 = va_arg(argp, const char *);
	
				CopyChars(dist, path1, true);

			}
			va_end(argp);                                  
		}
		void CombinePath(std::wstring* dist, const wchar_t* basePath, const wchar_t* path1, ...)
		{
			CopyChars(dist, basePath, false);
			va_list argp;
			va_start(argp, path1);
			while (path1)
			{
				dist->push_back('/');
				path1 = va_arg(argp, const wchar_t *);

				CopyChars(dist, path1, true);

			}
			va_end(argp);
		}


	private:
		bool CreateDirectoryA(const char* dir) const
		{
			return _mkdir(dir) == 0;
		}

		bool CreateDirectoryW(const wchar_t* dir) const
		{
			return _wmkdir(dir) == 0;
		}

		void CopyChars(std::string* dist, const char* src,bool checkHead )
		{
			size_t s = 0;
			size_t e = strlen(src) - 1;
			if (checkHead)
			{
				while (IsPathSeparator(src[s]))
				{
					s++;
				}
			}
			while (IsPathSeparator(src[e]) && s > 0)
			{
				e--;
			}

			for (size_t i = s; i <= e; i++)
			{
				dist->push_back(src[i]);
			}
		}

		void CopyChars(std::wstring* dist, const wchar_t* src, bool checkHead)
		{
			size_t s = 0;
			size_t e = wcslen(src) - 1;
			if (checkHead)
			{
				while (IsPathSeparator(src[s]))
				{
					s++;
				}
			}
			
			while (IsPathSeparator(src[e]) && s > 0)
			{
				e--;
			}

			for (size_t i = s; i <= e; i++)
			{
				dist->push_back(src[i]);
			}
		}

	};
}


