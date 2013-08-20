#pragma once

#include "GeometryCollection.h"
#include "Polygon.h"

namespace OSGeo
{
	namespace Ogr
	{
		/// <summary>Represents a collection of <see cref="Polygon"/> objects.</summary>
		[System::Diagnostics::DebuggerDisplay("Count = {Count}")]
		public ref class MultiPolygon : public GeometryCollection, Generic::IEnumerable<Polygon^>
		{
		private:
			/// <summary>The multi polygon.</summary>
			OGRMultiPolygon* _multiPolygon;
		internal:
			/// <summary>Initialises a new instance of the <see cref="FieldDefinitionCollection"/> class.</summary>
			/// <param name="featureDefinition">The OGR feature definition.</param>
			MultiPolygon(OGRMultiPolygon* multiPolygon);
		public:
			/// <summary>Returns an enumerator that iterates through a <see cref="GeometryCollection"/> containing <see cref="Polygon"/> objects.</summary>
			virtual Generic::IEnumerator<Polygon^>^ GetEnumerator() new = Generic::IEnumerable<Polygon^>::GetEnumerator;

			/// <summary>Gets the area of this instance.</summary>
			property double Area
			{
				double get();
			}
		};

		
		/// <summary>Supports a simple iteration over <see cref="Polygon"/> objects in a <see cref="MultiPolygon"/>.</summary>
		private ref class PolygonEnumerator : public Generic::IEnumerator<Polygon^>
		{
		private:
			/// <summary>The current geometry.</summary>
			Geometry^ _currentGeometry;
			
			/// <summary>The multi polygon.</summary>
			OGRMultiPolygon* _multiPolygon;
			
			/// <summary>Releases the current geometry,</summary>
			void ReleaseCurrentGeometry();
			
			/// <summary>The current index.</summary>
			int _currentIndex;
			
			/// <summary>Disposes this instance.</summary>
			virtual ~PolygonEnumerator();
		internal:
			/// <summary>Initialises a new instance of the <see cref="PolygonEnumerator"/> class.</summary>
			/// <param name="multiPolygon">The OGR multi-polygon.</param>
			PolygonEnumerator(OGRMultiPolygon* multiPolygon);
		public:
			/// <summary>Gets the <see cref="Polygon"/> in the <see cref="MultiPolygon"/> at the current position of the enumerator.</summary>
			property Polygon^ Current { 
				virtual Polygon^ get();
			};
			
			/// <summary>Gets the <see cref="Polygon"/> in the <see cref="MultiPolygon"/> at the current position of the enumerator.</summary>
			property Object^ CurrentBase { 
				virtual Object^ get() sealed = System::Collections::IEnumerator::Current::get;
			};
			
			/// <summary>Advances the enumerator to the next <see cref="Polygon"/> of the <see cref="MultiPolygon"/>.</summary>
			virtual bool MoveNext();
			
			/// <summary>Sets the enumerator to its initial position, which is before the first <see cref="Polygon"/> in the <see cref="MultiPolygon"/>.</summary>
			virtual void Reset();
		};
	}
}
