#pragma once
#include <math.h>

namespace geo
{
	class Point
	{
	public:
		Point()
			:x(0), y(0)
		{

		}

		Point(double x, double y)
			:x(x), y(y)
		{

		}

		Point(const Point& p)
			:x(p.x), y(p.y)
		{

		}
		~Point()
		{

		}

		Point& operator = (const Point& p)
		{
			if (this != &p)
			{
				this->x = p.x;
				this->y = p.y;
			}
			return *this;
		}

		bool operator == (const Point& p) const
		{
			return (x == p.x && y == p.y);
		}

		bool ApproximateEquals(const Point& p, double v) const
		{
			return abs(x - p.x) < v && abs(y - p.y) < v;
		}
	public:
		double x;
		double y;

	};
}
