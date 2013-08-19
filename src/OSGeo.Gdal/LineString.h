#pragma once

#include "Curve.h"

using namespace System::Collections;

namespace OSGeo
{
	namespace Ogr
	{
		/// <summary>Represents a line string.</summary>
		[System::Diagnostics::DebuggerDisplay("Count = {Count}")]
		public ref class LineString : public Curve, Generic::IList<PointGeometry^>
		{
		private:
			/// <summary>The OGR line string.</summary>
			OGRLineString* _lineString;
		internal:
			/// <summary>Initialises a new instance of the <see cref="LineString"/> class.</summary>
			LineString(OGRLineString* lineString);
		public:
			/// <summary>Initialises a new instance of the <see cref="LineString"/> class.</summary>
			LineString(void);
			
			/// <summary>Returns an enumerator that iterates through a <see cref="LineString"/> containing <see cref="PointGeometry"/> objects.</summary>
			virtual Generic::IEnumerator<PointGeometry^>^ GetEnumerator() sealed = Generic::IEnumerable<PointGeometry^>::GetEnumerator;
			
			/// <summary>Returns an enumerator that iterates through a <see cref="LineString"/> containing <see cref="PointGeometry"/> objects.</summary>
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
			virtual void Add(PointGeometry^ point);
			
			/// <summary>Adds a line string to this instance.</summary>
			virtual void Add(LineString^ lineString);
			
			/// <summary>Adds a segment of a line string to this instance.</summary>
			/// <param name="start">The first vertex to copy, defaults to 0 to start with the first vertex in the other line string.</param>
			/// <param name="start">The last vertex to copy, defaults to -1 indicating the last vertex of the other line string.</param>
			virtual void Add(LineString^ lineString, int start, int length);
			
			/// <summary>Clears this instance.</summary>
			virtual void Clear();
			
			/// <summary>Gets a value indicating whether this line contains the specified point.</summary>
			virtual bool Contains(PointGeometry^ point);
			
			/// <summary>Copies this instance to the specified array.</summary>
			virtual void CopyTo(array<PointGeometry^>^ destination, int index) = Generic::ICollection<PointGeometry^>::CopyTo;
			
			/// <summary>Removes the specified point.</summary>
			virtual bool Remove(PointGeometry^ point);
			
			/// <summary>Removes the point at the specified index.</summary>
			virtual void RemoveAt(int index);
			
			/// <summary>Gets the points.</summary>
			property PointGeometry^ Points[int]
			{
				virtual PointGeometry^ get(int index) = Generic::IList<PointGeometry^>::default::get;
				virtual void set(int index, PointGeometry^ value) = Generic::IList<PointGeometry^>::default::set;
			}
			
			/// <summary>Returns the index of the point on the line.</summary>
			virtual int IndexOf(PointGeometry^ point);
			
			/// <summary>Inserts a point at the specified index.</summary>
			virtual void Insert(int index, PointGeometry^ point);
		};
	}
}

