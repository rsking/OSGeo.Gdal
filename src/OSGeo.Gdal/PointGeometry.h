#pragma once
#include "Geometry.h"

namespace OSGeo
{
	namespace Ogr
	{
		public ref class PointGeometry : public Geometry
		{
		private:
			OGRPoint* _point;
		internal:
			PointGeometry(OGRPoint* point);
		public:
			property double X 
			{ 
				double get();
				void set(double value);
			};

			property double Y 
			{ 
				double get();
				void set(double value);
			};

			property double Z 
			{ 
				double get();
				void set(double value);
			};
		};
	}
}
