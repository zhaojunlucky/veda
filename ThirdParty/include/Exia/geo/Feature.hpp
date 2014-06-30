#pragma once
#include "GeoJSONBase.hpp"
#include "GeometryUtil.hpp"
#include <memory>

namespace geo
{
	namespace geojson
	{
		class Feature : public IGeoJSON
		{
		public:
			Feature(const GeoJSONGeometry& geometry, const GeoJSONProperties& prop)
			{
				CopyGeometry(geometry);
				CopyProp(prop);
			}
			Feature(const GeoJSONGeometry& geometry)
			{
				CopyGeometry(geometry);
			}

			Feature( GeoJSONGeometry* geometry,  GeoJSONProperties* prop)
			{
				mGeometry.reset(geometry);
				mProp.reset(prop);
			}
			Feature( GeoJSONGeometry* geometry)
			{
				mGeometry.reset(geometry);
			}

			Feature(const Feature& other)
			{
				CopyGeometry(*other.mGeometry.get());
				CopyProp(*other.mProp.get());
			}
			virtual ~Feature()
			{

			}

			virtual void FromJSON(const Json::Value& obj)
			{
				if (0 != strcmp(obj["type"].asCString(), "Feature"))
				{
					throw GeoJSONException("Json is not Feature.");
				}
				Json::Value prop = obj["properties"];
				if (!prop.isNull())
				{
					SetProperties(prop);
				}

				Json::Value geometry = obj["geometry"];
				std::shared_ptr<GeoJSONGeometry> g(GeometryUtil::CreateGeometryFromType(geometry["type"].asCString()));
				g->FromJSON(geometry);
				mGeometry = g;
			}
			virtual void ToJSON(Json::Value& obj)
			{
				obj["type"] = "Feature";
				if (mProp.get())
				{
					obj["properties"] = *mProp.get();
				}
				Json::Value g;
				mGeometry->ToJSON(g);
				obj["geometry"] = g;
			}

			void SetProperties(const GeoJSONProperties& prop)
			{
				CopyProp(prop);
			}

			void SetProperties( GeoJSONProperties* prop)
			{
				mProp.reset(prop);
			}

			const GeoJSONGeometry* GetGeometry() const
			{
				return mGeometry.get();
			}

			const GeoJSONProperties& GetProperties() const
			{
				return *mProp.get();
			}

			Feature& operator=(const Feature& other)
			{
				CopyGeometry(*other.mGeometry.get());
				CopyProp(*other.mProp.get());
			}
		private:
			void CopyGeometry(const GeoJSONGeometry& geometry)
			{
				mGeometry.reset(GeometryUtil::CreateGeometryFromOther(geometry));
			}

			void CopyProp(const GeoJSONProperties& prop)
			{
				mProp.reset(new GeoJSONProperties(prop));
			}
			friend class GeoJSON;
			Feature()
			{

			}
		private:
			std::shared_ptr<GeoJSONProperties> mProp;
			std::shared_ptr<GeoJSONGeometry> mGeometry;
		};
	}
}