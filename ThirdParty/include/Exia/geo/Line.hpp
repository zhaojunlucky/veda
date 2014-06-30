#pragma once
#include "Point.hpp"
namespace geo
{
	class Line
	{

	public:
		Line()
			:a(0), b(0), c(0)
		{

		}

		Line(const Line& line)
		{
			a = line.a;
			b = line.b;
			c = line.c;
		}

		Line& operator =(const Line& line)
		{
			if (this != &line)
			{
				a = line.a;
				b = line.b;
				c = line.c;
			}
			return *this;
		}

		Line(const Point& p1, const Point& p2)
		{
			a = p2.y - p1.y;
			b = p1.x - p2.x;
			c = p2.x*p1.y - p1.x*p2.y;
		}

		void ParallelMove(double distance)
		{
			c += distance;
		}

		double Distance(const Point& p)
		{
			return abs(a*p.x+b*p.y+c)/sqrt(a*a+b*b);
		}

		void CrossPoint(const Line& line, Point& p)
		{
			p.x = -(c*line.b - b*line.c) / (a*line.b - b*line.a);
			p.y = -(c*line.a - a*line.c) / (b*line.a - a*line.b);
		}

		bool IsParallel(const Line& line)
		{
			return (a == line.a && b == line.b);
		}
	public:
		double a;
		double b;
		double c;
	};
}