#pragma once
#include "Sort.h"
#include "Vector.h"
namespace veda
{
	template <class T>
	void convexHull(const Vector<T>& points, Vector<T>& p)
	{
		Vector<T> tmp = points;
		
		size_t minIndex = 0;
		for (size_t i = 1; i < points.getLength(); i++)
		{
			const auto& p1 = points[i];
			const auto& p2 = points[minIndex];
			if ((p1.y < p2.y) || (p1.y == p2.y && p1.x > p2.x))
			{
				minIndex = i;
			}
		}

		// get the min Y point
		auto minPoint = points[minIndex];
		Vector<std::pair<size_t, double>> seq;
		for (size_t i = 0; i < points.getLength() && i != minIndex; i++)
		{

		}
	}
}