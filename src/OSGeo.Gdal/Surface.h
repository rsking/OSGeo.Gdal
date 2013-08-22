#pragma once

#include "Geometry.h"

namespace OSGeo
{
	namespace Ogr
	{
		/// <summary>Represents a surface.</summary>
		public ref class Surface abstract : public Geometry
		{
		private:
			/// <summary>The OGR surface.</summary>
			OGRSurface* _surface;
		protected:			
			/// <summary>Initialises a new instance of the <see cref="Surface"/> class.</summary>
			/// <param name="surface">The OGR surface.</param>
			Surface(OGRSurface* surface);
		public:
			/// <summary>Gets the area of this instance.</summary>
			property double Area
			{
				double get();
			}
		};
	}
}

