#include "stdafx.h"
#include "PathUtil.h"
#include <direct.h>
#include <stdarg.h>

namespace veda
{
	PathUtil::PathUtil()
	{
	}


	PathUtil::~PathUtil()
	{
	}

	bool PathUtil::isPathSeparator(wchar_t c)
	{
		return (c == L'\\' || c == L'/');
	}

	bool PathUtil::isPathStartWithSeparator(const wchar_t* path)
	{
		return isPathSeparator(path[0]);
	}

	bool PathUtil::isPathEndWithSeparator(const wchar_t* path)
	{
		size_t l = wcslen(path) - 1;
		return isPathSeparator(path[l]);
	}

	wstring PathUtil::combinePath(const wchar_t* basePath, const wchar_t* path1, ...)
	{
		wstring path;
		copyChars(&path, basePath, false);
		path.push_back('/');
		copyChars(&path, path1, true);
		va_list argp;
		va_start(argp, path1);
		const wchar_t* p = NULL;
		while ((p = va_arg(argp, const wchar_t *)) != nullptr)
		{
			path.push_back('/');
			copyChars(&path, p, true);
		}
		va_end(argp);
		return std::move(path);
	}
	wstring PathUtil::trimPathLeftSeparator(const wchar_t* path)
	{
		wstring dist;

		size_t s = 0;
		size_t e = wcslen(path) - 1;
		while (isPathSeparator(path[s]))
		{
			s++;
		}
		dist.reserve(e-s+1);
		for (size_t i = s; i <= e; i++)
		{
			dist.push_back(path[i]);
		}

		return std::move(dist);
	}
	wstring PathUtil::trimPathRightSeparator(const wchar_t* path)
	{
		wstring dist;
		copyChars(&dist, path, false);
		return std::move(dist);
	}
	wstring PathUtil::trimPathSeparator(const wchar_t* path)
	{
		wstring dist;
		copyChars(&dist, path, true);
		return std::move(dist);
	}


	void PathUtil::copyChars(std::wstring* dist, const wchar_t* src, bool checkHead)
	{
		size_t s = 0;
		size_t e = wcslen(src) - 1;
		if (checkHead)
		{
			while (isPathSeparator(src[s]))
			{
				s++;
			}
		}

		while (isPathSeparator(src[e]) && s > 0)
		{
			e--;
		}
		dist->reserve(dist->size() + e - s + 1);
		for (size_t i = s; i <= e; i++)
		{
			dist->push_back(src[i]);
		}
	}


}