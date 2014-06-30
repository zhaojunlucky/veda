#pragma once
#include <exception>
#include "..\JsonCpp\json.h"
namespace geo
{
	namespace geojson
	{
		enum GeoJSONGeometryType
		{
			GPoint,
			GMultiPoint,
			GLineString,
			GMultiLineString,
			GPolygon,
			GMultiPolygon
		};

		class IGeoJSON
		{
		public:
			virtual ~IGeoJSON()
			{

			}

			virtual void FromJSON(const Json::Value& obj) = 0;
			virtual void ToJSON(Json::Value& obj) = 0;
		};


		static void JsonObject2MultiPoint(const Json::Value& obj, MultiPoint& multiPoint)
		{
			for (size_t i = 0; i < obj.size(); i++)
			{
				Json::Value point = obj[i];
				multiPoint.Add(new Point(point[(Json::Value::UInt)0].asDouble(), point[(Json::Value::UInt)1].asDouble()));
			}
		}


		static void MultiPoint2JsonObject(const MultiPoint& multiPoint, Json::Value& obj)
		{
			for (size_t i = 0; i < multiPoint.Size(); i++)
			{
				const Point* p = multiPoint.Get(i);
				Json::Value point;
				point.append(p->x);
				point.append(p->y);
				obj.append(point);
			}
		}

		class GeoJSONException : public std::exception
		{
		public:
			GeoJSONException(const char* message)
				:std::exception(message)
			{

			}
			virtual ~GeoJSONException()
			{

			}
		};

		class GeoJSONProperties : public Json::Value
		{
		public :
			GeoJSONProperties()
				:Json::Value()
			{

			}
			GeoJSONProperties(const Json::Value& v)
				:Json::Value(v)
			{

			}
			GeoJSONProperties(const GeoJSONProperties& v)
				:Json::Value(v)
			{

			}

			virtual ~GeoJSONProperties()
			{

			}

		};

		class GeoJSONGeometry : public IGeoJSON
		{
		public:
			GeoJSONGeometry(GeoJSONGeometryType type)
				:mType(type)
			{

			}
			virtual ~GeoJSONGeometry()
			{

			}

			GeoJSONGeometryType GetGeoJSONGeometryType() const
			{
				return mType;
			}

			virtual void FromJSON(const Json::Value& obj) = 0;
			virtual void ToJSON(Json::Value& obj) = 0;
		protected:
			GeoJSONGeometryType mType;
		};


	}
}
