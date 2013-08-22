#pragma once

#include "Geometry.h"

namespace OSGeo
{
	namespace Ogr
	{
		ref class Point;

		/// <summary>The curve geometry class.</summary>
		public ref class Curve abstract : public Geometry
		{
		private:
			/// <summary>The OGR curve</summary>
			OGRCurve* _curve;
		protected:
			/// <summary>Initialises a new instance of the <see cref="Curve"/> class.</summary>
			/// <param name="curve">The OGR curve.</param>
			Curve(OGRCurve* curve);
		public:
			/// <summary>Gets the length of the curve.</summary>
			property double Length
			{
				double get();
			}

			/// <summary>Gets the curve start point.</summary>
			property Point^ Start
			{
				Point^ get();
			}

			/// <summary>Gets the curve end point.</summary>
			property Point^ End
			{
				Point^ get();
			}

			/// <summary>Gets a value indicating whether this instance is closed.</summary>
			property bool IsClosed
			{
				bool get();
			}

			/// <summary>Gets a point at given distance along curve.</summary>
			Point^ GetPoint(double distance);
		};
	}
}

