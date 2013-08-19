#pragma once

#include <ogr_geometry.h>

using namespace System::Collections;

namespace OSGeo
{
	namespace Ogr
	{
		ref class PointGeometry;

		/// <summary>Supports a simple iteration over <see cref="PointGeometry"/> objects in a <see cref="LineString"/>.</summary>
		ref class PointGeometryEnumerator sealed : public Generic::IEnumerator<PointGeometry^>
		{
		private:
			/// <summary>The current point.</summary>
			PointGeometry^ _currentPoint;
			
			/// <summary>The current index.</summary>
			int _currentIndex;

			/// <summary>The OGR line string.</summary>
			OGRLineString* _lineString;
			
			/// <summary>Disposes this instance.</summary>
			virtual ~PointGeometryEnumerator();
		internal:
			/// <summary>Initialises a new instance of the <see cref="PointGeometryEnumerator"/> class.</summary>
			PointGeometryEnumerator(OGRLineString* lineString);
		public:
			/// <summary>Gets the <see cref="PointGeometry"/> in the <see cref="LineString"/> at the current position of the enumerator.</summary>
			property PointGeometry^ Current { 
				virtual PointGeometry^ get() sealed = Generic::IEnumerator<PointGeometry^>::Current::get;
			};

			/// <summary>Gets the <see cref="PointGeometry"/> in the <see cref="LineString"/> at the current position of the enumerator.</summary>
			property Object^ CurrentBase { 
				virtual Object^ get() sealed = System::Collections::IEnumerator::Current::get;
			};

			/// <summary>Advances the enumerator to the next <see cref="PointGeometry"/> of the <see cref="LineString"/>.</summary>
			virtual bool MoveNext();

			/// <summary>Sets the enumerator to its initial position, which is before the first <see cref="PointGeometry"/> in the <see cref="LineString"/>.</summary>
			virtual void Reset();
		};
	}
}
