#pragma once
#include "MultiPoint.hpp"
#include <vector>
#include "Vector.hpp"

namespace geo
{
	class Polygon
	{
	public:

		Polygon()
		{
			mPoints = new MultiPoint;
		}
		Polygon(MultiPoint* points)
		{
			mPoints = points;
		}
		Polygon(const MultiPoint& points)
		{
			mPoints = new MultiPoint(points);
		}

		Polygon(MultiPoint* points, const std::vector<MultiPoint*>& holes)
		{
			mPoints = points;
		}

		Polygon(const MultiPoint& points, const std::vector<MultiPoint>& holes)
		{
			mPoints = new MultiPoint(points);
		}

		Polygon(const Polygon& polygon)
		{
			mPoints = 0;
			CopyPolygon(polygon);
		}

		~Polygon()
		{
			delete mPoints;
			for (size_t i = 0; i < mHoles.size(); i++)
			{
				delete mHoles[i];
			}
			mHoles.clear();
		}

		const MultiPoint* GetPoints() const
		{
			return mPoints;
		}
		void DeleteAllHoles()
		{
			for (size_t i = 0; i < mHoles.size(); i++)
			{
				delete mHoles[i];
			}
			mHoles.clear();
		}

		MultiPoint* RemoveHole(size_t index)
		{
			MultiPoint* p = mHoles[index];
			mHoles.erase(mHoles.begin() + index);
			return p;
		}

		void DeleteHole(size_t index)
		{
			MultiPoint* hole = RemoveHole(index);
			delete hole;
		}

		void Set(MultiPoint* points)
		{
			if (mPoints)
			{
				delete mPoints;
			}
			mPoints = points;
			DeleteAllHoles();
		}

		void Set(MultiPoint* points, std::vector<MultiPoint*> holes)
		{
			Set(points);
			mHoles = holes;
		}

		size_t HoleSize() const
		{
			return mHoles.size();
		}

		void AddHole(const MultiPoint& hole)
		{
			AddHole(new MultiPoint(hole));
		}

		void AddHole(MultiPoint* hole)
		{
			mHoles.push_back(hole);
		}

		const MultiPoint* GetHole(size_t index) const
		{
			return mHoles[index];
		}

		Polygon& operator = (const Polygon& other)
		{
			if (this != &other)
			{
				CopyPolygon(other);
			}

			return *this;
		}

		bool IsClockWise() const
		{
			size_t max = 0;
			for (size_t i = 1; i < mPoints->Size() - 1; i++)
			{
				if ((*mPoints)[i].x >(*mPoints)[max].x)
				{
					max = i;
				}
			}

			size_t cur = max;
			size_t pre = (cur == 0 ? mPoints->Size() - 2 : cur - 1);
			size_t next = (cur == mPoints->Size() - 1 ? 1 : cur + 1);
			const Point* p0 = mPoints->Get(pre);
			const Point* p1 = mPoints->Get(cur);
			const Point* p2 = mPoints->Get(next);

			Vector v1(p1->x - p0->x, p1->y - p0->y);
			Vector v2(p2->x - p1->x, p2->y - p1->y);
			return v1.crossProduct(v2) < 0;
		}

		void Reverse()
		{
			mPoints->Reverse();
		}

	private:
		void CopyPolygon(const Polygon& other)
		{
			if (mPoints)
			{
				delete mPoints;
			}
			this->mPoints = new MultiPoint(*other.mPoints);
			DeleteAllHoles();
			for (size_t i = 0; i < other.HoleSize(); i++)
			{
				AddHole(*other.mHoles[i]);
			}
		}
	private:
		MultiPoint* mPoints;
		std::vector<MultiPoint*> mHoles;
	};
}