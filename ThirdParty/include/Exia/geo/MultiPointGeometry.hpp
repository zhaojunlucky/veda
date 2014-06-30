#pragma once
#include "GeoJSONBase.hpp"
#include "MultiPoint.hpp"
#include <memory>
namespace geo
{
	namespace geojson
	{
		class MultiPointGeometry : public GeoJSONGeometry
		{
		public:
			MultiPointGeometry()
				:GeoJSONGeometry(GeoJSONGeometryType::GMultiPoint)
			{
				multiPoint.reset(new MultiPoint);
			}

			MultiPointGeometry(const MultiPoint& p)
				:GeoJSONGeometry(GeoJSONGeometryType::GMultiPoint)
			{
				SetMultiPoint(p);
			}

			MultiPointGeometry(MultiPoint* p)
				:GeoJSONGeometry(GeoJSONGeometryType::GMultiPoint)
			{
				this->multiPoint.reset(p);
			}

			MultiPointGeometry(const MultiPointGeometry& other)
				:GeoJSONGeometry(GeoJSONGeometryType::GMultiPoint)
			{
				SetMultiPoint(*other.multiPoint.get());
			}

			void SetMultiPoint(const MultiPoint& p)
			{
				this->multiPoint.reset(new MultiPoint(p));
			}

			void SetMultiPoint(MultiPoint* p)
			{
				this->multiPoint.reset(p);
			}

			const MultiPoint* GetMultiPointPtr() const
			{
				return multiPoint.get();
			}

			const std::shared_ptr<MultiPoint> GetMultiPoint()
			{
				return multiPoint;
			}

			virtual ~MultiPointGeometry()
			{

			}
			virtual void FromJSON(const Json::Value& obj)
			{
				multiPoint->DeleteAll();

				if (0 != (strcmp(obj["type"].asCString(), "MultiPoint")))
				{
					throw GeoJSONException("Geometry is not MultiPoint.");
				}
				const Json::Value coordinates = obj["coordinates"];
				JsonObject2MultiPoint(coordinates, *multiPoint.get());
			}
			virtual void ToJSON(Json::Value& obj)
			{
				obj["type"] = "MultiPoint";
				Json::Value coordinates;
				MultiPoint2JsonObject(*multiPoint.get(), coordinates);
				obj["coordinates"] = coordinates;
			}

			MultiPointGeometry& operator = (const MultiPointGeometry& other)
			{
				if (this != &other)
				{
					SetMultiPoint(*other.multiPoint.get());;
				}
				
				return *this;
			}
		private:
			std::shared_ptr<MultiPoint> multiPoint;
		};
	}
}