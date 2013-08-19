#pragma once

#include "LineString.h"

namespace OSGeo
{
	namespace Ogr
	{
		/// <summary>Represents a linear ring.</summary>
		public ref class LinearRing sealed : public LineString
		{
		private:
			/// <summary>The linear ring.</summary>
			OGRLinearRing* _linearRing;
		internal:
			/// <summary>Initialises a new instance of the <see cref="LinearRing"/> class.</summary>
			LinearRing(OGRLinearRing* linearRing);
		public:
			/// <summary>Gets a value indicating whether this instance is close-wise.</summary>
			property bool IsClockwise
			{
				bool get();
			}
		};
	}
}
