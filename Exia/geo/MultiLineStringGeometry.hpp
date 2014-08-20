#pragma once
#include "GeoJSONBase.hpp"
#include "MultiLineString.hpp"
#include <memory>

namespace geo
{
	namespace geojson
	{
		class MultiLineStringGeometry : public GeoJSONGeometry
		{
		public:
			MultiLineStringGeometry()
				:GeoJSONGeometry(GeoJSONGeometryType::GMultiLineString)
			{
				multiLineString.reset(new MultiLineString);
			}

			MultiLineStringGeometry(const MultiLineString& p)
				:GeoJSONGeometry(GeoJSONGeometryType::GMultiLineString)
			{
				SetMultiLineString(p);
			}

			MultiLineStringGeometry( MultiLineString* p)
				:GeoJSONGeometry(GeoJSONGeometryType::GMultiLineString)
			{
				SetMultiLineString(p);
			}

			MultiLineStringGeometry(const MultiLineStringGeometry& other)
				:GeoJSONGeometry(GeoJSONGeometryType::GMultiLineString)
			{
				SetMultiLineString(*other.multiLineString.get());
			}

			void SetMultiLineString(const MultiLineString& p)
			{
				this->multiLineString.reset(new MultiLineString(p));
			}

			void SetMultiLineString( MultiLineString* p)
			{
				this->multiLineString.reset(p);
			}

			const MultiLineString* GetMultiLineStringPtr() const
			{
				return multiLineString.get();
			}

			const std::shared_ptr<MultiLineString> GetMultiLineString()
			{
				return multiLineString;
			}

			virtual ~MultiLineStringGeometry()
			{

			}
			virtual void FromJSON(const Json::Value& obj)
			{
				multiLineString->DeleteAll();

				if (0 != (strcmp(obj["type"].asCString(), "MultiLineString")))
				{
					throw GeoJSONException("Geometry is not MultiLineString.");
				}
				const Json::Value coordinates = obj["coordinates"];

				for (size_t i = 0; i < coordinates.size(); i++)
				{
					LineString* ls = new LineString();
					JsonObject2MultiPoint(coordinates[i], *ls);
					multiLineString->Add(ls);
				}
			}
			virtual void ToJSON(Json::Value& obj)
			{
				obj["type"] = "MultiLineString";
				Json::Value coordinates;
				for (size_t i = 0; i < multiLineString->Size(); i++)
				{
					Json::Value ls;
					MultiPoint2JsonObject(*multiLineString->Get(i), ls);
					coordinates.append(ls);
				}
				
				obj["coordinates"] = coordinates;
			}

			MultiLineStringGeometry& operator = (const MultiLineStringGeometry& other)
			{
				if (this != &other)
				{				
					SetMultiLineString(*other.multiLineString.get());
				}
				return *this;
			}
		private:
			std::shared_ptr<MultiLineString> multiLineString;
		};
	}
}