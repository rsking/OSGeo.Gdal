#pragma once

#include "Geometry.h"

namespace OSGeo
{
	namespace Ogr
	{
		/// <summary>The point geometry class.</summary>
		public ref class PointGeometry sealed : public Geometry
		{
		private:
			/// <summary>The point.</summary>
			OGRPoint* _point;

			/// <summary>Coordinate values.</summary>
			double _x, _y, _z;
		internal:
			/// <summary>Initialises a new instance of the <see cref="PointGeometry"/> class.</summary>
			PointGeometry(OGRPoint* point);
			
			/// <summary>Initialises a new instance of the <see cref="PointGeometry"/> class.</summary>
			PointGeometry(double x, double y, double z);
		public:
			/// <summary>Gets or sets the x-coordinate.</summary>
			property double X 
			{ 
				double get();
				void set(double value);
			};
			
			/// <summary>Gets or sets the y-coordinate.</summary>
			property double Y 
			{ 
				double get();
				void set(double value);
			};
			
			/// <summary>Gets or sets the z-coordinate.</summary>
			property double Z 
			{ 
				double get();
				void set(double value);
			};
		};
	}
}
