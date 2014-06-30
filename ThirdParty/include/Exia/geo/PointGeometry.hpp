#pragma once
#include "GeoJSONBase.hpp"
#include "Point.hpp"
#include <memory>
namespace geo
{
	namespace geojson
	{
		class PointGeometry : public GeoJSONGeometry
		{
		public:
			PointGeometry()
				:GeoJSONGeometry(GeoJSONGeometryType::GPoint)
			{
				this->p.reset(new Point);
			}

			PointGeometry(const Point& p)
				:GeoJSONGeometry(GeoJSONGeometryType::GPoint)
			{
				this->p.reset(new Point(p));
			}

			PointGeometry(Point* p)
				:GeoJSONGeometry(GeoJSONGeometryType::GPoint)
			{
				SetPoint(p);
			}

			PointGeometry(const PointGeometry& other)
				:GeoJSONGeometry(GeoJSONGeometryType::GPoint)
			{
				*p.get() = *other.p.get();
			}

			void SetPoint(const Point& p)
			{
				*this->p.get() = p;
			}

			void SetPoint(Point* p)
			{
				this->p.reset(p);
			}

			const Point* GetPointPtr() const
			{
				return p.get();
			}

			const std::shared_ptr<Point> GetPoint()
			{
				return p;
			}

			virtual ~PointGeometry()
			{

			}
			virtual void FromJSON(const Json::Value& obj)
			{
				if (0 != (strcmp(obj["type"].asCString(),"Point")))
				{
					throw GeoJSONException("Geometry is not point.");
				}
				Json::Value coordinates = obj["coordinates"];
				p->x = coordinates[(Json::Value::UInt)0].asDouble();
				p->y = coordinates[(Json::Value::UInt)1].asDouble();
			}
			virtual void ToJSON(Json::Value& obj)
			{
				obj["type"] = "Point";
				Json::Value coordinates;

				coordinates.append(p->x);
				coordinates.append(p->y);
				obj["coordinates"] = coordinates;
			}

			PointGeometry& operator = (const PointGeometry& other)
			{
				if (this != &other)
				{
					*this->p.get() = *other.p.get();
				}
				
				return *this;
			}
		private:
			std::shared_ptr<Point> p;
		};
	}
}