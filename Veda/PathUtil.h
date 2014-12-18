#pragma once
#include <string>
using namespace std;
#include "veda.h"
#include "ZString.h"
namespace veda
{
	class VEDA_EXPORT PathUtil
	{
	public:
		PathUtil();
		~PathUtil();

		static bool isPathSeparator(wchar_t c) ;
		static bool isPathStartWithSeparator(const wchar_t* path);
		static bool isPathEndWithSeparator(const wchar_t* path) ;
		/**
		 * must pass 'NULL' as the last paramater
		 */
		StringPtr combinePath(const wchar_t* basePath, const wchar_t* path1, ...);
		StringPtr trimPathLeftSeparator(const wchar_t* path);
		StringPtr trimPathRightSeparator(const wchar_t* path);
		StringPtr trimPathSeparator(const wchar_t* path);
	private:
		void copyChars(String* dist, const wchar_t* src, bool checkHead);
	};


}


