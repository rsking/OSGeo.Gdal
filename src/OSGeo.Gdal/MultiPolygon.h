#pragma once

#include "GeometryCollection.h"
#include "Polygon.h"

namespace OSGeo
{
	namespace Ogr
	{
		ref class MultiPolygon : public GeometryCollection, Generic::IEnumerable<Polygon^>
		{
		private:
			OGRMultiPolygon* _multiPolygon;
		internal:
			MultiPolygon(OGRMultiPolygon* multiPolygon);
		public:
			virtual Generic::IEnumerator<Polygon^>^ GetEnumeratorPolygon() sealed = Generic::IEnumerable<Polygon^>::GetEnumerator;

			property double Area
			{
				double get();
			}
		};

		private ref class PolygonEnumerator : public Generic::IEnumerator<Polygon^>
		{
		private:
			Geometry^ _currentGeometry;
			OGRMultiPolygon* _multiPolygon;
			void ReleaseCurrentGeometry();
			int _currentIndex;
		public:
			PolygonEnumerator(OGRMultiPolygon* multiPolygon);
			property Polygon^ Current { 
				virtual Polygon^ get();
			};

			property Object^ CurrentBase { 
				virtual Object^ get() sealed = IEnumerator::Current::get;
			};

			virtual bool MoveNext();

			virtual void Reset();

			virtual ~PolygonEnumerator();
		};
	}
}
