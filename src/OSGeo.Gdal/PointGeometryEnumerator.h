#pragma once

#include <ogr_geometry.h>

using namespace System::Collections;

namespace OSGeo
{
	namespace Ogr
	{
		ref class PointGeometry;

		ref class PointGeometryEnumerator : public Generic::IEnumerator<PointGeometry^>
		{
		private:
			PointGeometry^ _currentPoint;
			int _currentIndex;
			OGRLineString* _lineString;
		internal:
			PointGeometryEnumerator(OGRLineString* lineString);
		public:
			property PointGeometry^ Current { 
				virtual PointGeometry^ get();
			};

			property Object^ CurrentBase { 
				virtual Object^ get() sealed = IEnumerator::Current::get;
			};

			virtual bool MoveNext();

			virtual void Reset();

			virtual ~PointGeometryEnumerator();
		};
	}
}
