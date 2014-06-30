#pragma once
#include <Windows.h>

namespace zhui
{
	class __declspec(dllexport) Point
	{
	public:
		Point(int x, int y)
			:x(x), y(y)
		{

		}
		Point(const Point& point)
		{
			x = point.x;
			y = point.y;
		}
		Point()
		{

		}

		Point& operator = (const Point& point)
		{
			x = point.x;
			y = point.y;
			return *this;
		}
	public:
		int x;
		int y;
	};
	class Size
	{
	public:
		Size(size_t width, size_t height)
			:width(width), height(height)
		{

		}
		Size(const Size& size)
		{
			width = size.width;
			height = size.height;
		}
		Size()
		{

		}
		Size& operator=(const Size& size)
		{
			width = size.width;
			height = size.height;
			return *this;
		}
	public:
		size_t width;
		size_t height;
	};
	struct ZFormPara
	{

		UINT appIcon;
		UINT appIconSmall;
		Point point;
		Size size;
	};
}


