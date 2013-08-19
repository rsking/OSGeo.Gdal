#pragma once

#include "Surface.h"

namespace OSGeo
{
	namespace Ogr
	{
		ref class LinearRing;
		
		/// <summary>Represents a polygon.</summary>
		public ref class Polygon sealed : public Surface
		{
		private:
			/// <summary>The OGR polygon.</summary>
			OGRPolygon* _polygon;
		internal:
			/// <summary>Initialises a new instance of the <see cref="Polygon"/> class.</summary>
			/// <param name="surface">The OGR polygon.</param>
			Polygon(OGRPolygon* polygon);
		public:
			/// <summary>Initialises a new instance of the <see cref="Polygon"/> class.</summary>
			Polygon();

			/// <summary>Gets the out ring.</summary>
			property LinearRing^ Outer
			{
				LinearRing^ get();
			}

			/// <summary>Clones this instance.</summary>
			virtual Geometry^ Clone() override;
		};
	}
}

