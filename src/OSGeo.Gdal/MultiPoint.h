#pragma once

#include "GeometryCollection.h"

namespace OSGeo
{
	namespace Ogr
	{
		ref class Point;

		/// <summary>Represents a collection of <see cref="Point"/> objects.</summary>
		[System::Diagnostics::DebuggerDisplay("Count = {Count}")]
		public ref class MultiPoint : public GeometryCollection, Generic::IEnumerable<Point^>
		{
		private:
			/// <summary>The multi Point.</summary>
			OGRMultiPoint* _multiPoint;

			/// <summary>Supports a simple iteration over <see cref="Point"/> objects in a <see cref="MultiPoint"/>.</summary>
			ref class Enumerator : public Generic::IEnumerator<Point^>
			{
			private:
				/// <summary>The current geometry.</summary>
				Geometry^ _currentGeometry;
			
				/// <summary>The multi Point.</summary>
				OGRMultiPoint* _multiPoint;
			
				/// <summary>Releases the current geometry,</summary>
				void ReleaseCurrentGeometry();
			
				/// <summary>The current index.</summary>
				int _currentIndex;
			
				/// <summary>Disposes this instance.</summary>
				virtual ~Enumerator();
			internal:
				/// <summary>Initialises a new instance of the <see cref="Enumerator"/> class.</summary>
				/// <param name="multiPoint">The OGR multi-Point.</param>
				Enumerator(OGRMultiPoint* multiPoint);
			public:
				/// <summary>Gets the <see cref="Point"/> in the <see cref="MultiPoint"/> at the current position of the enumerator.</summary>
				property Point^ Current { 
					virtual Point^ get();
				};
			
				/// <summary>Gets the <see cref="Point"/> in the <see cref="MultiPoint"/> at the current position of the enumerator.</summary>
				property Object^ CurrentBase { 
					virtual Object^ get() sealed = System::Collections::IEnumerator::Current::get;
				};
			
				/// <summary>Advances the enumerator to the next <see cref="Point"/> of the <see cref="MultiPoint"/>.</summary>
				virtual bool MoveNext();
			
				/// <summary>Sets the enumerator to its initial position, which is before the first <see cref="Point"/> in the <see cref="MultiPoint"/>.</summary>
				virtual void Reset();
			};
		internal:
			/// <summary>Initialises a new instance of the <see cref="FieldDefinitionCollection"/> class.</summary>
			/// <param name="featureDefinition">The OGR feature definition.</param>
			MultiPoint(OGRMultiPoint* multiPoint);
		public:
			/// <summary>Returns an enumerator that iterates through a <see cref="GeometryCollection"/> containing <see cref="Point"/> objects.</summary>
			virtual Generic::IEnumerator<Point^>^ GetEnumerator() new = Generic::IEnumerable<Point^>::GetEnumerator;
		};
	}
}
