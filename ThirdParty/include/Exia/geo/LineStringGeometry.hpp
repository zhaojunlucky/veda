#pragma once
#include "GeoJSONBase.hpp"
#include "LineString.hpp"
#include <memory>
namespace geo
{
	namespace geojson
	{
		class LineStringGeometry : public GeoJSONGeometry
		{
		public:
			LineStringGeometry()
				:GeoJSONGeometry(GeoJSONGeometryType::GLineString)
			{
				lineString.reset(new LineString);
			}

			LineStringGeometry(const LineString& p)
				:GeoJSONGeometry(GeoJSONGeometryType::GLineString)
			{
				SetLineString(p);
			}

			LineStringGeometry( LineString* p)
				:GeoJSONGeometry(GeoJSONGeometryType::GLineString)
			{
				lineString.reset(p);
			}

			LineStringGeometry(const LineStringGeometry& other)
				:GeoJSONGeometry(GeoJSONGeometryType::GLineString)
			{
				SetLineString(*other.lineString.get());
			}

			void SetLineString(const LineString& p)
			{
				this->lineString.reset(new LineString(p));
			}

			void SetLineString( LineString* p)
			{
				this->lineString.reset(p);
			}

			const LineString* GetLineStringPtr() const
			{
				return lineString.get();
			}

			const std::shared_ptr<LineString> GetLineString()
			{
				return lineString;
			}

			virtual ~LineStringGeometry()
			{

			}
			virtual void FromJSON(const Json::Value& obj)
			{
				if (0 != (strcmp(obj["type"].asCString(), "LineString")))
				{
					throw GeoJSONException("Geometry is not LineString.");
				}
				const Json::Value coordinates = obj["coordinates"];
				lineString->DeleteAll();
				JsonObject2MultiPoint(coordinates, *lineString.get());
			}
			virtual void ToJSON(Json::Value& obj)
			{
				obj["type"] = "LineString";
				Json::Value coordinates;
				MultiPoint2JsonObject(*lineString.get(), coordinates);
				obj["coordinates"] = coordinates;
			}

			LineStringGeometry& operator = (const LineStringGeometry& other)
			{
				if (this != &other)
				{
					SetLineString(*other.lineString.get());
				}
				return *this;
			}
		private:
			std::shared_ptr<LineString> lineString;
		};
	}
}