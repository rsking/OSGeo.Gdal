#pragma once
#include "Geometry.h"

namespace OSGeo
{
	namespace Ogr
	{
		public ref class Surface abstract : public Geometry
		{
		private:
			OGRSurface* _surface;
		protected:
			Surface();
			Surface(OGRSurface* surface);
			virtual void SetGeometryObject(OGRGeometry* geometry) override;
		public:
			property double Area
			{
				double get();
			}
		};
	}
}

