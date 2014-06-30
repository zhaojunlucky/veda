#pragma once
#include "Point.hpp"
#include "GeoCollection.hpp"

namespace geo
{
	class MultiPoint : public GeoCollection<Point>
	{
	public:
		MultiPoint()
		{

		}
		

		MultiPoint(const MultiPoint& other)
		{
			for (size_t i = 0; i < other.Size(); i++)
			{
				AddCopy(*other.Get(i));
			}
		}

		MultiPoint& operator = (const MultiPoint& other)
		{
			if (this != &other)
			{
				this->DeleteAll();
				for (size_t i = 0; i < other.Size(); i++)
				{
					AddCopy(*other.Get(i));
				}
			}
			return *this;
		}

		virtual void AddCopy(const Point& v)
		{
			Add(new Point(v));
		}
		
	};

}