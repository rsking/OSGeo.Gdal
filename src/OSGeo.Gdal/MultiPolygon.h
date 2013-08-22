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

			/// <summary>Supports a simple iteration over <see cref="Polygon"/> objects in a <see cref="MultiPolygon"/>.</summary>
			ref class Enumerator : public Generic::IEnumerator<Polygon^>
			{
			private:
				/// <summary>The current geometry.</summary>
				Polygon^ _currentPolygon;
			
				/// <summary>The multi polygon.</summary>
				OGRMultiPolygon* _multiPolygon;
			
				/// <summary>Releases the current geometry,</summary>
				void ReleaseCurrentGeometry();
			
				/// <summary>The current index.</summary>
				int _currentIndex;
			
				/// <summary>Disposes this instance.</summary>
				virtual ~Enumerator();
			internal:
				/// <summary>Initialises a new instance of the <see cref="Enumerator"/> class.</summary>
				/// <param name="multiPolygon">The OGR multi-polygon.</param>
				Enumerator(OGRMultiPolygon* multiPolygon);
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
		internal:
			/// <summary>Initialises a new instance of the <see cref="FieldDefinitionCollection"/> class.</summary>
			/// <param name="featureDefinition">The OGR feature definition.</param>
			MultiPolygon(OGRMultiPolygon* multiPolygon);
		public:
			/// <summary>Returns an enumerator that iterates through a <see cref="GeometryCollection"/> containing <see cref="Polygon"/> objects.</summary>
			virtual Generic::IEnumerator<Polygon^>^ GetEnumerator() = Generic::IEnumerable<Polygon^>::GetEnumerator;

			virtual Generic::IEnumerator<Geometry^>^ GetEnumeratorGeometry() override;

			//virtual Generic::IEnumerator<Geometry^>^ GetEnumerator() 

			/// <summary>Gets the area of this instance.</summary>
			property double Area
			{
				double get();
			}
		};
	}
}
