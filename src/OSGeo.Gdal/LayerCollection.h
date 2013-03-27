#pragma once

#include <ogrsf_frmts.h>

using namespace System;
using namespace System::Collections;

namespace OSGeo 
{
	namespace Ogr
	{
		ref class Layer;

		public ref class LayerCollection : public Generic::IEnumerable<Layer^>
		{
		private:
			OGRDataSource* _dataSource;
		internal:
			LayerCollection(OGRDataSource* dataSource);
		public:
			property int Count
			{
				int get();
			}

			virtual Generic::IEnumerator<Layer^>^ GetEnumerator() sealed = Generic::IEnumerable<Layer^>::GetEnumerator;

			virtual IEnumerator^ GetEnumeratorBase() sealed = IEnumerable::GetEnumerator;
		};

		private ref class LayerEnumerator : public Generic::IEnumerator<Layer^>
		{
		private:
			int _currentIndex;
			Layer^ _currentLayer;
			OGRDataSource* _dataSource;
			void ReleaseCurrentLayer();
		public:
			LayerEnumerator(OGRDataSource* _dataSource);
			property Layer^ Current { 
				virtual Layer^ get();
			};

			property Object^ CurrentBase { 
				virtual Object^ get() sealed = IEnumerator::Current::get;
			};

			virtual bool MoveNext();

			virtual void Reset();

			virtual ~LayerEnumerator();
		};
	}
}
