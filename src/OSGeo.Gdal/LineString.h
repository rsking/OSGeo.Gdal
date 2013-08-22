#pragma once

#include "Curve.h"

using namespace System::Collections;

namespace OSGeo
{
	namespace Ogr
	{
		/// <summary>Represents a line string.</summary>
		[System::Diagnostics::DebuggerDisplay("Count = {Count}")]
		public ref class LineString : public Curve, Generic::IList<Point^>
		{
		private:
			/// <summary>The OGR line string.</summary>
			OGRLineString* _lineString;

			/// <summary>Supports a simple iteration over <see cref="PointGeometry"/> objects in a <see cref="LineString"/>.</summary>
			ref class PointEnumerator sealed : public Generic::IEnumerator<Point^>
			{
			private:
				/// <summary>The current point.</summary>
				Point^ _currentPoint;
			
				/// <summary>The current index.</summary>
				int _currentIndex;

				/// <summary>The OGR line string.</summary>
				OGRLineString* _lineString;
			
				/// <summary>Disposes this instance.</summary>
				virtual ~PointEnumerator();
			internal:
				/// <summary>Initialises a new instance of the <see cref="PointGeometryEnumerator"/> class.</summary>
				PointEnumerator(OGRLineString* lineString);
			public:
				/// <summary>Gets the <see cref="PointGeometry"/> in the <see cref="LineString"/> at the current position of the enumerator.</summary>
				property Point^ Current { 
					virtual Point^ get() sealed = Generic::IEnumerator<Point^>::Current::get;
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
		internal:
			/// <summary>Initialises a new instance of the <see cref="LineString"/> class.</summary>
			LineString(OGRLineString* lineString);
		public:
			/// <summary>Initialises a new instance of the <see cref="LineString"/> class.</summary>
			LineString(void);
			
			/// <summary>Returns an enumerator that iterates through a <see cref="LineString"/> containing <see cref="Point"/> objects.</summary>
			virtual Generic::IEnumerator<Point^>^ GetEnumerator() sealed = Generic::IEnumerable<Point^>::GetEnumerator;
			
			/// <summary>Returns an enumerator that iterates through a <see cref="LineString"/> containing <see cref="Point"/> objects.</summary>
			virtual IEnumerator^ GetEnumeratorBase() sealed = IEnumerable::GetEnumerator;
			
			/// <summary>Gets or sets the number of points.</summary>
			property int Count
			{
				virtual int get();
				virtual void set(int value);
			}
			
			/// <summary>Gets a value indicating whether this instance is read-only.</summary>
			property bool IsReadOnly
			{
				virtual bool get();
			}
			
			/// <summary>Adds a point to this instance.</summary>
			virtual void Add(Point^ point);
			
			/// <summary>Adds a line string to this instance.</summary>
			virtual void Add(LineString^ lineString);
			
			/// <summary>Adds a segment of a line string to this instance.</summary>
			/// <param name="start">The first vertex to copy, defaults to 0 to start with the first vertex in the other line string.</param>
			/// <param name="start">The last vertex to copy, defaults to -1 indicating the last vertex of the other line string.</param>
			virtual void Add(LineString^ lineString, int start, int length);
			
			/// <summary>Clears this instance.</summary>
			virtual void Clear();
			
			/// <summary>Gets a value indicating whether this line contains the specified point.</summary>
			virtual bool Contains(Point^ point);
			
			/// <summary>Copies this instance to the specified array.</summary>
			virtual void CopyTo(array<Point^>^ destination, int index) = Generic::ICollection<Point^>::CopyTo;
			
			/// <summary>Removes the specified point.</summary>
			virtual bool Remove(Point^ point);
			
			/// <summary>Removes the point at the specified index.</summary>
			virtual void RemoveAt(int index);
			
			/// <summary>Gets the points.</summary>
			property Point^ Points[int]
			{
				virtual Point^ get(int index) = Generic::IList<Point^>::default::get;
				virtual void set(int index, Point^ value) = Generic::IList<Point^>::default::set;
			}
			
			/// <summary>Returns the index of the point on the line.</summary>
			virtual int IndexOf(Point^ point);
			
			/// <summary>Inserts a point at the specified index.</summary>
			virtual void Insert(int index, Point^ point);
		};
	}
}

