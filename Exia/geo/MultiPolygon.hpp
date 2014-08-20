#pragma once
#include "GeoCollection.hpp"
#include "Polygon.hpp"

namespace geo
{
	class MultiPolygon : public GeoCollection<Polygon>
	{
	public:
		MultiPolygon()
		{

		}


		MultiPolygon(const MultiPolygon& other)
		{
			for (size_t i = 0; i < other.Size(); i++)
			{
				AddCopy(*other.Get(i));
			}
		}

		MultiPolygon& operator = (const MultiPolygon& other)
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

		virtual void AddCopy(const Polygon& v)
		{
			Add(new Polygon(v));
		}

	};
}