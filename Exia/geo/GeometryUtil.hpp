#pragma once
#include "GeoJSONBase.hpp"
#include "PointGeometry.hpp"
#include "MultiLineStringGeometry.hpp"
#include "LineStringGeometry.hpp"
#include "MultiPointGeometry.hpp"
#include "PolygonGeometry.hpp"
#include "MultiPolygonGeometry.hpp"
#include "../JsonCpp/json.h"


namespace geo
{
	namespace geojson
	{
		class GeometryUtil
		{
		public:
			static GeoJSONGeometry* CreateGeometryFromOther(const GeoJSONGeometry& geometry)
			{
				if (geometry.GetGeoJSONGeometryType() == GeoJSONGeometryType::GPoint)
				{
					return new PointGeometry(*(PointGeometry*)&geometry);
				}
				else if (geometry.GetGeoJSONGeometryType() == GeoJSONGeometryType::GMultiPoint)
				{
					return new MultiPointGeometry(*(MultiPointGeometry*)&geometry);
				}else if (geometry.GetGeoJSONGeometryType() == GeoJSONGeometryType::GLineString)
				{
					return new LineStringGeometry(*(LineStringGeometry*)&geometry);
				}
				else if (geometry.GetGeoJSONGeometryType() == GeoJSONGeometryType::GMultiLineString)
				{
					return new MultiLineStringGeometry(*(MultiLineStringGeometry*)&geometry);
				}
				else if (geometry.GetGeoJSONGeometryType() == GeoJSONGeometryType::GPolygon)
				{
					return new PolygonGeometry(*(PolygonGeometry*)&geometry);
				}
				else if (geometry.GetGeoJSONGeometryType() == GeoJSONGeometryType::GMultiPolygon)
				{
					return new MultiPolygonGeometry(*(MultiPolygonGeometry*)&geometry);
				}
				else
				{
					return 0;
				}
			}

			static GeoJSONGeometry* CreateGeometryFromType(const char* type)
			{
				if (0 == strcmp("Point",type))
				{
					return new PointGeometry();
				}
				else if (0 == strcmp("MultiPoint", type))
				{
					return new MultiPointGeometry();
				}
				else if (0 == strcmp("LineString", type))
				{
					return new LineStringGeometry();
				}
				else if (0 == strcmp("MultiLineString", type))
				{
					return new MultiLineStringGeometry();
				}
				else if (0 == strcmp("Polygon", type))
				{
					return new PolygonGeometry();
				}
				else if (0 == strcmp("MultiPolygon", type))
				{
					return new MultiPolygonGeometry();
				}
				else
				{
					return 0;
				}
			}
		};


	}
}