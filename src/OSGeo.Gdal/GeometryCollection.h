#pragma once

#include "Geometry.h"

using namespace System;
using namespace System::Collections;

namespace OSGeo
{
	namespace Ogr
	{
		/// <summary>Represents a collection of <see cref="Geometry"/> objects.</summary>
		[System::Diagnostics::DebuggerDisplay("Count = {Count}")]
		public ref class GeometryCollection : public Geometry, Generic::IEnumerable<Geometry^>
		{
		private:
			/// <summary>The geometry collection.</summary>
			OGRGeometryCollection* _geometryCollection;

			/// <summary>Supports a simple iteration over <see cref="Geometry"/> objects in a <see cref="OGRGeometryCollection"/>.</summary>
			ref class Enumerator sealed : public Generic::IEnumerator<Geometry^>
			{
			private:
				/// <summary>The current geometry,</summary>
				Geometry^ _currentGeometry;

				/// <summary>The geometry collection.</summary>
				OGRGeometryCollection* _geometryCollection;
			
				/// <summary>Releases the current geometry.</summary>
				void ReleaseCurrentGeometry();
			
				/// <summary>The current index.</summary>
				int _currentIndex;
			internal:
				/// <summary>Disposes this instance.</summary>
				virtual ~Enumerator();

				/// <summary>Initialises a new instance of the <see	cref="Enumerator"/> class.</summary>
				Enumerator(OGRGeometryCollection* geometryCollection);
			public:
				/// <summary>Gets the <see cref="Geometry"/> in the <see cref="GeometryCollection"/> at the current position of the enumerator.</summary>
				property Geometry^ Current { 
					virtual Geometry^ get();
				};
			
				/// <summary>Gets the <see cref="Geometry"/> in the <see cref="GeometryCollection"/> at the current position of the enumerator.</summary>
				property Object^ CurrentBase { 
					virtual Object^ get() sealed = System::Collections::IEnumerator::Current::get;
				};

				/// <summary>Advances the enumerator to the next <see cref="Geometry"/> of the <see cref="GeometryCollection"/>.</summary>
				virtual bool MoveNext();

				/// <summary>Sets the enumerator to its initial position, which is before the first <see cref="Geometry"/> in the <see cref="GeometryCollection"/>.</summary>
				virtual void Reset();
			};
		internal:
			/// <summary>Initialises a new instance of the <see cref="GeometryCollection"/> class.</summary>
			/// <param name="featureDefinition">The OGR feature definition.</param>
			GeometryCollection(OGRGeometryCollection* geometryCollection);
		public:
			/// <summary>Returns an enumerator that iterates through a collection containing <see cref="Geometry"/> objects.</summary>
			virtual Generic::IEnumerator<Geometry^>^ GetEnumeratorGeometry() = Generic::IEnumerable<Geometry^>::GetEnumerator;
			
			/// <summary>Returns an enumerator that iterates through a collection containing <see cref="Geometry"/> objects.</summary>
			virtual IEnumerator^ GetEnumeratorBase() = System::Collections::IEnumerable::GetEnumerator;
			
			/// <summary>Gets the number of <see cref="Geometry"/> objects in the collection.</summary>
			property int Count
			{
				int get();
			}
		};
	}
}
