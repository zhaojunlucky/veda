#pragma once
#include "GeoJSONBase.hpp"
#include "Polygon.hpp"
#include <memory>
namespace geo
{
	namespace geojson
	{
		class PolygonGeometry : public GeoJSONGeometry
		{
		public:
			PolygonGeometry()
				:GeoJSONGeometry(GeoJSONGeometryType::GPolygon)
			{
				polygon.reset(new Polygon);
			}

			PolygonGeometry(const Polygon& p)
				:GeoJSONGeometry(GeoJSONGeometryType::GPolygon)
			{
				SetPolygon(p);
			}
			PolygonGeometry(Polygon* p)
				:GeoJSONGeometry(GeoJSONGeometryType::GPolygon)
			{
				SetPolygon(p);
			}


			PolygonGeometry(const PolygonGeometry& other)
				:GeoJSONGeometry(GeoJSONGeometryType::GPolygon)
			{
				SetPolygon(*other.polygon.get());
			}

			void SetPolygon(const Polygon& p)
			{
				this->polygon.reset(new Polygon(p));
			}

			void SetPolygon( Polygon* p)
			{
				this->polygon.reset(p);
			}

			const Polygon* GetPolygonPtr() const
			{
				return polygon.get();
			}

			const std::shared_ptr<Polygon> GetPolygon()
			{
				return polygon;
			}

			virtual ~PolygonGeometry()
			{

			}
			virtual void FromJSON(const Json::Value& obj)
			{
				if (0 != (strcmp(obj["type"].asCString(), "Polygon")))
				{
					throw GeoJSONException("Geometry is not Polygon.");
				}
				const Json::Value coordinates = obj["coordinates"];
				
				MultiPoint points;
				
				JsonObject2MultiPoint(coordinates[(Json::Value::UInt)0], points);
				polygon.reset(new Polygon(points));
				for (size_t i = 1; i < coordinates.size(); i++)
				{
					MultiPoint* hole = new MultiPoint();
					JsonObject2MultiPoint(coordinates[i], *hole);
					polygon->AddHole(hole);
				}

				
				
			}
			virtual void ToJSON(Json::Value& obj)
			{
				obj["type"] = "Polygon";
				Json::Value coordinates;
				Json::Value points;
				MultiPoint2JsonObject(*polygon->GetPoints(), points);
				coordinates.append(points);

				for (size_t i = 0; i < polygon->HoleSize(); i++)
				{
					Json::Value hole;
					MultiPoint2JsonObject(*polygon->GetHole(i), hole);
					coordinates.append(hole);
				}

				obj["coordinates"] = coordinates;
			}

			PolygonGeometry& operator = (const PolygonGeometry& other)
			{
				if (this != &other)
				{
					SetPolygon(*other.polygon.get());
				}

				return *this;
			}
		private:
			std::shared_ptr<Polygon> polygon;
		};
	}
}