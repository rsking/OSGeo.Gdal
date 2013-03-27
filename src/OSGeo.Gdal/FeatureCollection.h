#pragma once
#include <ogrsf_frmts.h>
#include "Feature.h"

using namespace System::Collections;

namespace OSGeo
{
	namespace Ogr
	{
		public ref class FeatureCollection : public Generic::IEnumerable<Feature^>
		{
		private:
			OGRLayer* _layer;
		internal:
			FeatureCollection(OGRLayer* layer);
		public:
			virtual Generic::IEnumerator<Feature^>^ GetEnumerator() sealed = Generic::IEnumerable<Feature^>::GetEnumerator;

			virtual IEnumerator^ GetEnumeratorBase() sealed = IEnumerable::GetEnumerator;

			property int Count
			{
				int get();
			}
		};

		private ref class FeatureEnumerator : public Generic::IEnumerator<Feature^>
		{
		private:
			Feature^ _currentFeature;
			OGRLayer* _layer;
			void ReleaseCurrentFeature();
		public:
			FeatureEnumerator(OGRLayer* layer);
			property Feature^ Current { 
				virtual Feature^ get();
			};

			property Object^ CurrentBase { 
				virtual Object^ get() sealed = IEnumerator::Current::get;
			};

			virtual bool MoveNext();

			virtual void Reset();

			virtual ~FeatureEnumerator();
		};
	}
}
