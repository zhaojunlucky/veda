#pragma once
#include "GeoCollection.hpp"
#include "LineString.hpp"

namespace geo
{
	class MultiLineString : public GeoCollection<LineString>
	{
	public:
		MultiLineString()
		{

		}
		
		MultiLineString(const MultiLineString& other)
		{
			for (size_t i = 0; i < other.Size(); i++)
			{
				AddCopy(*other.Get(i));
			}
		}

		MultiLineString& operator = (const MultiLineString& other)
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

		void AddCopy(const LineString& v)
		{
			Add(new LineString(v));
		}
	};
}