#pragma once

#include "Geometry.h"

namespace OSGeo
{
	namespace Ogr
	{
		ref class PointGeometry;

		/// <summary>The curve geometry class.</summary>
		public ref class Curve abstract : public Geometry
		{
		private:
			/// <summary>The OGR curve</summary>
			OGRCurve* _curve;
		protected:
			/// <summary>Initialises a new instance of the <see cref="Curve"/> class.<summary>
			Curve();

			/// <summary><summary>
			Curve(OGRCurve* surface);
		public:
			/// <summary>Gets the length of the curve.</summary>
			property double Length
			{
				double get();
			}

			/// <summary>Gets the curve start point.</summary>
			property PointGeometry^ Start
			{
				PointGeometry^ get();
			}

			/// <summary>Gets the curve end point.</summary>
			property PointGeometry^ End
			{
				PointGeometry^ get();
			}

			/// <summary>Gets a value indicating whether this instance is closed.</summary>
			property bool IsClosed
			{
				bool get();
			}

			/// <summary>Gets a point at given distance along curve.</summary>
			PointGeometry^ GetPoint(double distance);
		};
	}
}

