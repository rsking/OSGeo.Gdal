#pragma once

#include "GeometryCollection.h"

namespace OSGeo
{
	namespace Ogr
	{
		ref class LineString;

		/// <summary>Represents a collection of <see cref="LineString"/> objects.</summary>
		[System::Diagnostics::DebuggerDisplay("Count = {Count}")]
		public ref class MultiLineString : public GeometryCollection, Generic::IEnumerable<LineString^>
		{
		private:
			/// <summary>The multi LineString.</summary>
			OGRMultiLineString* _multiLineString;

			/// <summary>Supports a simple iteration over <see cref="LineString"/> objects in a <see cref="MultiLineString"/>.</summary>
			ref class Enumerator : public Generic::IEnumerator<LineString^>
			{
			private:
				/// <summary>The current geometry.</summary>
				Geometry^ _currentGeometry;
			
				/// <summary>The multi LineString.</summary>
				OGRMultiLineString* _multiLineString;
			
				/// <summary>Releases the current geometry,</summary>
				void ReleaseCurrentGeometry();
			
				/// <summary>The current index.</summary>
				int _currentIndex;
			
				/// <summary>Disposes this instance.</summary>
				virtual ~Enumerator();
			internal:
				/// <summary>Initialises a new instance of the <see cref="Enumerator"/> class.</summary>
				/// <param name="multiLineString">The OGR multi-LineString.</param>
				Enumerator(OGRMultiLineString* multiLineString);
			public:
				/// <summary>Gets the <see cref="LineString"/> in the <see cref="MultiLineString"/> at the current position of the enumerator.</summary>
				property LineString^ Current { 
					virtual LineString^ get();
				};
			
				/// <summary>Gets the <see cref="LineString"/> in the <see cref="MultiLineString"/> at the current position of the enumerator.</summary>
				property Object^ CurrentBase { 
					virtual Object^ get() sealed = System::Collections::IEnumerator::Current::get;
				};
			
				/// <summary>Advances the enumerator to the next <see cref="LineString"/> of the <see cref="MultiLineString"/>.</summary>
				virtual bool MoveNext();
			
				/// <summary>Sets the enumerator to its initial position, which is before the first <see cref="LineString"/> in the <see cref="MultiLineString"/>.</summary>
				virtual void Reset();
			};
		internal:
			/// <summary>Initialises a new instance of the <see cref="FieldDefinitionCollection"/> class.</summary>
			/// <param name="featureDefinition">The OGR feature definition.</param>
			MultiLineString(OGRMultiLineString* multiLineString);
		public:
			/// <summary>Returns an enumerator that iterates through a <see cref="GeometryCollection"/> containing <see cref="LineString"/> objects.</summary>
			virtual Generic::IEnumerator<LineString^>^ GetEnumerator() new = Generic::IEnumerable<LineString^>::GetEnumerator;
		};
	}
}
