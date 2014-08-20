#pragma once
#include "GeoJSONBase.hpp"
#include "Feature.hpp"
#include "GeoCollection.hpp"

namespace geo
{
	namespace geojson
	{
		class GeoJSON : public IGeoJSON, public GeoCollection<Feature>
		{
		public:
			GeoJSON()
			{

			}
			GeoJSON(const GeoJSON& other)
			{
				CopyFeatures(other);
			}

			virtual ~GeoJSON()
			{

			}
			virtual void FromJSON(const Json::Value& obj)
			{
				DeleteAll();
				if (0 != strcmp(obj["type"].asCString(), "FeatureCollection"))
				{
					throw GeoJSONException("Json is not a GeoJSON."); 
				}

				Json::Value features = obj["features"];
				for (size_t i = 0; i < features.size(); i++)
				{
					Json::Value feature = features[i];
					Feature* f = new Feature();
					f->FromJSON(feature);
					Add(f);
				}

			}
			virtual void ToJSON(Json::Value& obj)
			{
				obj["type"] = "FeatureCollection";
				Json::Value features;
				for (size_t i = 0; i < Size(); i++)
				{
					Feature* f = mData[i];
					Json::Value feature;
					f->ToJSON(feature);
					features.append(feature);
				}
				obj["features"] = features;
			}

			GeoJSON& operator = (const GeoJSON& other)
			{
				if (this != &other)
				{
					CopyFeatures(other);
				}
				return *this;
			}

			void AddCopy(const Feature & f)
			{
				Add(new Feature(f));
			}


		private:
			void CopyFeatures(const GeoJSON& other)
			{
				DeleteAll();
				for (size_t i = 0; i < other.Size(); i++)
				{
					AddCopy(*other.Get(i));
				}
			}
		};
	}
}
