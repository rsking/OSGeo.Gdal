#pragma once
#include <ogrsf_frmts.h>

using namespace System::Collections;

namespace OSGeo
{
	namespace Ogr
	{
		ref class Geometry;

		public ref class GeometryCollection : public Generic::IEnumerable<Geometry^>
		{
		private:
			OGRGeometry* _geometry;
		internal:
			GeometryCollection(OGRGeometry* geometry);
		public:
			virtual Generic::IEnumerator<Geometry^>^ GetEnumerator() sealed = Generic::IEnumerable<Geometry^>::GetEnumerator;

			virtual IEnumerator^ GetEnumeratorBase() sealed = IEnumerable::GetEnumerator;

			property int Count
			{
				int get();
			}
		};

		private ref class GeometryEnumerator : public Generic::IEnumerator<Geometry^>
		{
		private:
			Geometry^ _currentGeometry;
			OGRGeometry* _geometry;
			void ReleaseCurrentGeometry();
		public:
			GeometryEnumerator(OGRGeometry* geometry);
			property Geometry^ Current { 
				virtual Geometry^ get();
			};

			property Object^ CurrentBase { 
				virtual Object^ get() sealed = IEnumerator::Current::get;
			};

			virtual bool MoveNext();

			virtual void Reset();

			virtual ~GeometryEnumerator();
		};
	}
}
