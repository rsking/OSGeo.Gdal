#pragma once
#include <ogrsf_frmts.h>
#include "Feature.h"

using namespace System::Collections;

namespace OSGeo
{
	namespace Ogr
	{
		/// <summary>Represents a collection of features.</summary>
		[System::Diagnostics::DebuggerDisplay("Count = {Count}")]
		public ref class FeatureCollection sealed : public Generic::IEnumerable<Feature^>
		{
		private:
			/// <summary>The OGR layer.</summary>
			OGRLayer* _layer;

			/// <summary>Supports a simple iteration over <see cref="Feature"/> objects in a <see cref="Layer"/>.</summary>
			ref class FeatureEnumerator : public Generic::IEnumerator<Feature^>
			{
			private:
				/// <summary>The current feature.</summary>
				Feature^ _currentFeature;

				/// <summary>The OGR layer.</summary>
				OGRLayer* _layer;

				/// <summary>Releases the current feature.</summary>
				void ReleaseCurrentFeature();
			internal:
				/// <summary>Initialises a new instance of the <see cref="FeatureEnumerator"/> class.</summary>
				/// <param name="layer">The OGR layer.</param>
				FeatureEnumerator(OGRLayer* layer);
			public:			
				/// <summary>Gets the <see cref="Feature"/> in the <see cref="Layer"/> at the current position of the enumerator.</summary>
				property Feature^ Current { 
					virtual Feature^ get();
				};

				/// <summary>Gets the <see cref="Feature"/> in the <see cref="Layer"/> at the current position of the enumerator.</summary>
				property Object^ CurrentBase { 
					virtual Object^ get() sealed = System::Collections::IEnumerator::Current::get;
				};

				/// <summary>Advances the enumerator to the next <see cref="Feature"/> of the <see cref="Layer"/>.</summary>
				virtual bool MoveNext();

				/// <summary>Sets the enumerator to its initial position, which is before the first <see cref="Feature"/> in the <see cref="Layer"/>.</summary>
				virtual void Reset();

				/// <summary>Disposes this instance.</summary>
				virtual ~FeatureEnumerator();
			};
		internal:
			/// <summary>Initialises a new instance of the <see cref="FeatureCollection"/> class.</summary>
			/// <param name="layer">The OGR layer.</param>
			FeatureCollection(OGRLayer* layer);
		public:
			/// <summary>Returns an enumerator that iterates through a <see cref="Layer"/> of <see cref="Feature"/> objects.</summary>
			virtual Generic::IEnumerator<Feature^>^ GetEnumerator() sealed = Generic::IEnumerable<Feature^>::GetEnumerator;

			/// <summary>Returns an enumerator that iterates through a <see cref="Layer"/> of <see cref="Feature"/> objects.</summary>
			virtual IEnumerator^ GetEnumeratorBase() sealed = System::Collections::IEnumerable::GetEnumerator;

			/// <summary>Gets the number of <see cref="Feature"/> objects in the <see cref="Layer"/>.</summary>
			property int Count
			{
				int get();
			}

			/// <summary>Gets or sets the feature with the specified FID value.</summary>
			property Feature^ default[long]
			{
				Feature^ get(long fid);
				void set(long fid, Feature^ feature);
			}				
		};
	}
}
