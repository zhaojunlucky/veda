#pragma once
#include "GeoJSONBase.hpp"
#include "GeometryUtil.hpp"
#include "MultiPolygon.hpp"
#include <memory>
namespace geo
{
	namespace geojson
	{
		class MultiPolygonGeometry : public GeoJSONGeometry
		{
		public:
			MultiPolygonGeometry()
				:GeoJSONGeometry(GeoJSONGeometryType::GMultiPolygon)
			{
				multiPolygon.reset(new MultiPolygon);
			}

			MultiPolygonGeometry(const MultiPolygon& p)
				:GeoJSONGeometry(GeoJSONGeometryType::GMultiPolygon)
			{
				SetMultiPolygon(p);
			}

			MultiPolygonGeometry( MultiPolygon* p)
				:GeoJSONGeometry(GeoJSONGeometryType::GMultiPolygon)
			{
				SetMultiPolygon(p);
			}

			MultiPolygonGeometry(const MultiPolygonGeometry& other)
				:GeoJSONGeometry(GeoJSONGeometryType::GMultiPolygon)
			{
				SetMultiPolygon(*other.multiPolygon.get());
			}

			void SetMultiPolygon(const MultiPolygon& p)
			{
				this->multiPolygon.reset(new MultiPolygon(p));;
			}

			void SetMultiPolygon( MultiPolygon* p)
			{
				this->multiPolygon.reset(p);;
			}

			const MultiPolygon* GetMultiPolygonPtr() const
			{
				return multiPolygon.get();
			}
			const std::shared_ptr<MultiPolygon> GetMultiPolygon()
			{
				return multiPolygon;
			}
			virtual ~MultiPolygonGeometry()
			{

			}
			virtual void FromJSON(const Json::Value& obj)
			{
				multiPolygon->DeleteAll();
				if (0 != (strcmp(obj["type"].asCString(), "MultiPolygon")))
				{
					throw GeoJSONException("Geometry is not MultiPolygon.");
				}
				const Json::Value coordinates = obj["coordinates"];

				for (size_t i = 0; i < coordinates.size(); i++)
				{
					Json::Value polygonJson = coordinates[i];

					MultiPoint points;
					JsonObject2MultiPoint(polygonJson[(Json::Value::UInt)0], points);

					Polygon* p = new Polygon(points);
					for (size_t j = 1; j < polygonJson.size(); j++)
					{
						MultiPoint* hole = new MultiPoint();
						JsonObject2MultiPoint(polygonJson[i], *hole);
						p->AddHole(hole);
					}
					multiPolygon->Add(p);
				}
			}
			virtual void ToJSON(Json::Value& obj)
			{
				obj["type"] = "MultiPolygon";
				Json::Value coordinates;
				for (size_t i = 0; i < multiPolygon->Size(); i++)
				{
					const Polygon* polygon = multiPolygon->Get(i);
					Json::Value polygonCoordinates;
					Json::Value points;
					MultiPoint2JsonObject(*polygon->GetPoints(), points);
					polygonCoordinates.append(points);

					for (size_t i = 0; i < polygon->HoleSize(); i++)
					{
						Json::Value hole;
						MultiPoint2JsonObject(*polygon->GetHole(i), hole);
						polygonCoordinates.append(hole);
					}
					coordinates.append(polygonCoordinates);
				}

				obj["coordinates"] = coordinates;
			}

			MultiPolygonGeometry& operator = (const MultiPolygonGeometry& other)
			{
				if (this != &other)
				{
					SetMultiPolygon(*other.multiPolygon.get());
				}
				
				return *this;
			}
		private:
			std::shared_ptr<MultiPolygon> multiPolygon;
		};
	}
}