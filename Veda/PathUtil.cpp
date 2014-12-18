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

	StringPtr PathUtil::combinePath(const wchar_t* basePath, const wchar_t* path1, ...)
	{
		StringPtr path(new String());
		copyChars(path.get(), basePath, false);
		path->append('/');
		copyChars(path.get(), path1, true);
		va_list argp;
		va_start(argp, path1);
		const wchar_t* p = NULL;
		while ((p = va_arg(argp, const wchar_t *)) != nullptr)
		{
			path->append('/');
			copyChars(path.get(), p, true);
		}
		va_end(argp);
		return path;
	}
	StringPtr PathUtil::trimPathLeftSeparator(const wchar_t* path)
	{
		String* dist = new String;

		size_t s = 0;
		size_t e = wcslen(path) - 1;
		while (isPathSeparator(path[s]))
		{
			s++;
		}
		dist->reserve(e-s+1);
		for (size_t i = s; i <= e; i++)
		{
			dist->append(path[i]);
		}

		return makeStringPtr(dist);
	}
	StringPtr PathUtil::trimPathRightSeparator(const wchar_t* path)
	{
		String* dist = new String;
		copyChars(dist, path, false);
		return makeStringPtr(dist);
	}
	StringPtr PathUtil::trimPathSeparator(const wchar_t* path)
	{
		String* dist = new String;
		copyChars(dist, path, true);
		return makeStringPtr(dist);
	}


	void PathUtil::copyChars(String* dist, const wchar_t* src, bool checkHead)
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
		dist->reserve(dist->getSize() + e - s + 1);
		for (size_t i = s; i <= e; i++)
		{
			dist->append(src[i]);
		}
	}


}