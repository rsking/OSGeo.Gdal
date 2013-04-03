#pragma once

#include "Curve.h"

using namespace System::Collections;

namespace OSGeo
{
	namespace Ogr
	{
		public ref class LineString : public Curve, Generic::IList<PointGeometry^>
		{
		private:
			OGRLineString* _lineString;
		internal:
			LineString(OGRLineString* lineString);
		public:
			LineString(void);
			virtual Generic::IEnumerator<PointGeometry^>^ GetEnumerator() sealed = Generic::IEnumerable<PointGeometry^>::GetEnumerator;

			virtual IEnumerator^ GetEnumeratorBase() sealed = IEnumerable::GetEnumerator;

			property int Count
			{
				virtual int get();
				virtual void set(int value);
			}

			property bool IsReadOnly
			{
				virtual bool get();
			}

			virtual void Add(PointGeometry^ point);

			virtual void Add(LineString^ lineString);

			virtual void Add(LineString^ lineString, int start, int length);

			virtual void Clear();

			virtual bool Contains(PointGeometry^ point);

			virtual void CopyTo(array<PointGeometry^>^ destination, int index) = Generic::ICollection<PointGeometry^>::CopyTo;

			virtual bool Remove(PointGeometry^ point);

			virtual void RemoveAt(int index);

			property PointGeometry^ Points[int]
			{
				virtual PointGeometry^ get(int index) = Generic::IList<PointGeometry^>::default::get;
				virtual void set(int index, PointGeometry^ value) = Generic::IList<PointGeometry^>::default::set;
			}

			virtual int IndexOf(PointGeometry^ point);

			virtual void Insert(int index, PointGeometry^ point);
		};
	}
}

