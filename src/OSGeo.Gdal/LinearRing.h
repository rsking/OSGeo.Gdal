#pragma once

#include "LineString.h"

namespace OSGeo
{
	namespace Ogr
	{
		public ref class LinearRing : public LineString
		{
		private:
			OGRLinearRing* _linearRing;
		internal:
			LinearRing(OGRLinearRing* linearRing);
		public:
			property bool IsClockwise
			{
				bool get();
			}
		};
	}
}
