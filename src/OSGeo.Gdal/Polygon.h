#pragma once

#include "Surface.h"

namespace OSGeo
{
	namespace Ogr
	{
		ref class LinearRing;

		public ref class Polygon : public Surface
		{
		private:
			OGRPolygon* _polygon;
		internal:
			Polygon(OGRPolygon* polygon);
		public:
			Polygon();

			property LinearRing^ Outer
			{
				LinearRing^ get();
			}

			virtual Geometry^ Clone() override;
		};
	}
}

