#pragma once

#include <ogrsf_frmts.h>

using namespace System;
using namespace System::Collections;

namespace OSGeo 
{
	namespace Ogr
	{
		ref class Layer;

		/// <summary>Represents a collection of <see cref="Layer"/> objects in a <see cref="DataSource"/>.</summary>
		[System::Diagnostics::DebuggerDisplay("Count = {Count}")]
		public ref class LayerCollection sealed : public Generic::IEnumerable<Layer^>
		{
		private:
			/// <summary>The data source.</summary>
			OGRDataSource* _dataSource;

			/// <summary></summary>
			ref class Enumerator sealed : public Generic::IEnumerator<Layer^>
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
				virtual ~Enumerator();
			
				/// <summary>Initialises a new instance of the <see cref="Enumerator"/> class.</summary>
				/// <param name="layer">The OGR data source.</param>
				Enumerator(OGRDataSource* _dataSource);
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
		internal:
			/// <summary>Initialises a new instance of the <see cref="LayerCollection"/> class.</summary>
			/// <param name="dataSource">The OGR data source.</param>
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
	}
}
