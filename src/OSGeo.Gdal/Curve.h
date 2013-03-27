#pragma once

#include "Geometry.h"

namespace OSGeo
{
	namespace Ogr
	{
		ref class PointGeometry;

		public ref class Curve abstract : public Geometry
		{
		private:
			OGRCurve* _curve;
		protected:
			Curve();
			Curve(OGRCurve* surface);
			virtual void SetGeometryObject(OGRGeometry* geometry) override;
		public:
			// Gets the length of the curve.
			property double Length
			{
				double get();
			}

			// Gets the curve start point.
			property PointGeometry^ Start
			{
				PointGeometry^ get();
			}

			// Gets the curve end point.
			property PointGeometry^ End
			{
				PointGeometry^ get();
			}

			// Gets a value indicating whether this instance is closed.
			property bool IsClosed
			{
				bool get();
			}

			// Gets a point at given distance along curve.
			PointGeometry^ GetPoint(double distance);
		};
	}
}

