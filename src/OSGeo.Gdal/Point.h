#pragma once

#include "Geometry.h"

namespace OSGeo
{
	namespace Ogr
	{
		/// <summary>The point geometry class.</summary>
		public ref class Point sealed : public Geometry
		{
		private:
			/// <summary>The point.</summary>
			OGRPoint* _point;
		internal:
			/// <summary>Initialises a new instance of the <see cref="PointGeometry"/> class.</summary>
			Point(OGRPoint* point);
		public:
			/// <summary>Initialises a new instance of the <see cref="PointGeometry"/> class.</summary>
			Point(void);

			/// <summary>Initialises a new instance of the <see cref="PointGeometry"/> class.</summary>
			Point(double x, double y);

			/// <summary>Initialises a new instance of the <see cref="PointGeometry"/> class.</summary>
			Point(double x, double y, double z);

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
