#pragma once

#include <ogr_feature.h>

namespace OSGeo
{
	namespace Ogr
	{
		ref class Geometry;

		public ref class Feature
		{
		private:
			Geometry^ _geometry;
			OGRFeature* _feature;
			~Feature();
			!Feature();
		internal:
			Feature(OGRFeature* feature);
		public:
			property Geometry^ Geometry
			{
				OSGeo::Ogr::Geometry^ get();
			}
		};
	}
}