#pragma once

#include "Geometry.h"

using namespace System;
using namespace System::Collections;

namespace OSGeo
{
	namespace Ogr
	{
		public ref class GeometryCollection : public Geometry, Generic::IEnumerable<Geometry^>
		{
		private:
			OGRGeometryCollection* _geometryCollection;
		internal:
			GeometryCollection(OGRGeometryCollection* geometryCollection);
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
			OGRGeometryCollection* _geometryCollection;
			void ReleaseCurrentGeometry();
			int _currentIndex;
		public:
			GeometryEnumerator(OGRGeometryCollection* geometryCollection);
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
