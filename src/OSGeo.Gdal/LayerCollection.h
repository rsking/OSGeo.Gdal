#pragma once

#include <ogrsf_frmts.h>

using namespace System;
using namespace System::Collections;

namespace OSGeo 
{
	namespace Ogr
	{
		ref class Layer;

		/// <summary></summary>
		public ref class LayerCollection sealed : public Generic::IEnumerable<Layer^>
		{
		private:
			/// <summary>The data source.</summary>
			OGRDataSource* _dataSource;
		internal:
			/// <summary>Initialises a new instance of the <see cref="LayerCollection"/> class.</summary>
			/// <param name="layer">The OGR data source.</param>
			LayerCollection(OGRDataSource* dataSource);
		public:
			/// <summary>Gets the number of layers.</summary>
			property int Count
			{
				int get();
			}
			
			/// <summary>Returns an enumerator that iterates through a <see cref="DataSource"/> containing <see cref="Layer"/> objects.</summary>
			virtual Generic::IEnumerator<Layer^>^ GetEnumerator() sealed = Generic::IEnumerable<Layer^>::GetEnumerator;
			
			/// <summary>Returns an enumerator that iterates through a <see cref="DataSource"/> containing <see cref="Layer"/> objects.</summary>
			virtual IEnumerator^ GetEnumeratorBase() sealed = System::Collections::IEnumerable::GetEnumerator;
		};
		
		/// <summary></summary>
		private ref class LayerEnumerator sealed : public Generic::IEnumerator<Layer^>
		{
		private:
			/// <summary>The current index.</summary>
			int _currentIndex;
			
			/// <summary>The current layer,</summary>
			Layer^ _currentLayer;
			
			/// <summary>The data source.</summary>
			OGRDataSource* _dataSource;
			
			/// <summary>Releases the current layer.</summary>
			void ReleaseCurrentLayer();
		internal:
			/// <summary>Disposes this instance.</summary>
			virtual ~LayerEnumerator();
			
			/// <summary>Initialises a new instance of the <see cref="LayerEnumerator"/> class.</summary>
			/// <param name="layer">The OGR data source.</param>
			LayerEnumerator(OGRDataSource* _dataSource);
		public:			
			/// <summary>Gets the <see cref="Layer"/> in the <see cref="DataSource"/> at the current position of the enumerator.</summary>
			property Layer^ Current { 
				virtual Layer^ get();
			};
			
			/// <summary>Gets the <see cref="Layer"/> in the <see cref="DataSource"/> at the current position of the enumerator.</summary>
			property Object^ CurrentBase { 
				virtual Object^ get() sealed = System::Collections::IEnumerator::Current::get;
			};
			
			/// <summary>Advances the enumerator to the next <see cref="Layer"/> of the <see cref="DataSource"/>.</summary>
			virtual bool MoveNext();
			
			/// <summary>Sets the enumerator to its initial position, which is before the first <see cref="Layer"/> in the <see cref="DataSource"/>.</summary>
			virtual void Reset();
		};
	}
}
