#pragma once

#include "ogr_spatialref.h"

namespace OSGeo
{
	namespace Ogr
	{
		ref class SpatialReference;
		ref class Point;

		public ref class CoordinateTransformation
		{
		private:
			OGRCoordinateTransformation* _coordinateTransformation;
			SpatialReference^ _source;
			SpatialReference^ _target;
		public:
			CoordinateTransformation(SpatialReference^ source, SpatialReference^ target);

			Point^ Transform(Point^ point);

			void Transform(System::Collections::Generic::IList<Point^>^ points);

			void Transform(array<double>^ point);

			property SpatialReference^ Source
			{
				SpatialReference^ get();
			}

			property SpatialReference^ Target
			{
				SpatialReference^ get();
			}
		};
	}
}
