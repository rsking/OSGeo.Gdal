#pragma once

#include "FieldDefinition.h"

using namespace System;
using namespace System::Collections;

namespace OSGeo 
{
	namespace Ogr
	{
		ref class FeatureDefinition;

		/// <summary>Represents a collection of <see cref="FieldDefinition"/> objects.</summary>
		public ref class FieldDefinitionCollection sealed : public Generic::IList<FieldDefinition^>
		{
		private:
			/// <summary>The feature definition.</summary>
			OGRFeatureDefn* _featureDefinition;

			/// <summary>The field definitions.</summary>
			Generic::IDictionary<int, FieldDefinition^>^ _fieldDefinitions;
		internal:
			/// <summary>Initialises a new instance of the <see cref="FieldDefinitionCollection"/> class.</summary>
			/// <param name="featureDefinition">The OGR feature definition.</param>
			FieldDefinitionCollection(OGRFeatureDefn* featureDefinition);
		public:
			/// <summary>Returns an enumerator that iterates through a <see cref="FeatureDefinition"/> containing <see cref="FieldDefinition"/> objects.</summary>
			virtual Generic::IEnumerator<FieldDefinition^>^ GetEnumerator() sealed = Generic::IEnumerable<FieldDefinition^>::GetEnumerator;

			/// <summary>Returns an enumerator that iterates through a <see cref="FeatureDefinition"/> containing <see cref="FieldDefinition"/> objects.</summary>
			virtual IEnumerator^ GetEnumeratorBase() sealed = System::Collections::IEnumerable::GetEnumerator;

			/// <summary>Gets the field definition at the specified index.</summary>
			property FieldDefinition^ Item[int]
			{
				virtual FieldDefinition^ get(int index) = Generic::IList<FieldDefinition^>::default::get;
				virtual void set(int index, FieldDefinition^ value) = Generic::IList<FieldDefinition^>::default::set;
			}

			/// <summary>Gets the field definition with the specified name.</summary>
			property FieldDefinition^ Item[String^]
			{
				FieldDefinition^ get(String^ name);
			}
			
			/// <summary>Gets the number of <see cref="FieldDefinition"/> objects in the <see cref="FeatureDefinition"/>.</summary>
			virtual property int Count
			{
				int get();
			}
			
			/// <summary>Gets a value indicating whether this instance is read-only.</summary>
			virtual property bool IsReadOnly
			{
				bool get();
			}

			/// <summary>Adds a field to the collection.</summary>
			virtual void Add(FieldDefinition^ field);
			
			/// <summary>Clears this collection/</summary>
			virtual void Clear();
			
			/// <summary>Determines whether this instance contains the specified field.</summary>
			virtual bool Contains(FieldDefinition^ field);
			
			/// <summary>Copies this instance to another array at the specified location.</summary>
			virtual void CopyTo(array<FieldDefinition^>^ destination, int index);
			
			/// <summary>Removes the specified field from the collection.</summary>
			virtual bool Remove(FieldDefinition^ field);
			
			/// <summary>Removes the field at the specified index from the collection.</summary>
			virtual void RemoveAt(int index);
			
			/// <summary>Gets the index of the specified field.</summary>
			virtual int IndexOf(FieldDefinition^ field);
			
			/// <summary>Inserts the specified field at the specified index.</summary>
			virtual void Insert(int index, FieldDefinition^ field);
		};

		/// <summary>Supports a simple iteration over <see cref="FieldDefinition"/> objects in a <see cref="FeatureDefinition"/>.</summary>
		private ref class FieldDefinitionEnumerator sealed : public Generic::IEnumerator<FieldDefinition^>
		{
		private:
			/// <summary>The current index.</summary>
			int _currentIndex;
			
			/// <summary>The current field definition.</summary>
			FieldDefinition^ _currentFieldDefinition;
			
			/// <summary>The feature definition.</summary>
			OGRFeatureDefn* _featureDefinition;

			/// <summary>Disposes this instance.</summary>
			virtual ~FieldDefinitionEnumerator();
			
			/// <summary>Releases the current field definition.</summary>
			void ReleaseCurrentFieldDefinition();
		internal:
			/// <summary>Initialises a new instance of the <see cref="FieldDefinitionEnumerator"/> class.</summary>
			/// <param name="layer">The OGR feature definition.</param>
			FieldDefinitionEnumerator(OGRFeatureDefn* layer);
		public:		
			/// <summary>Gets the <see cref="FieldDefinition"/> in the <see cref="FeatureDefinition"/> at the current position of the enumerator.</summary>
			property FieldDefinition^ Current { 
				virtual FieldDefinition^ get();
			};
					
			/// <summary>Gets the <see cref="FieldDefinition"/> in the <see cref="FeatureDefinition"/> at the current position of the enumerator.</summary>
			property Object^ CurrentBase { 
				virtual Object^ get() sealed = System::Collections::IEnumerator::Current::get;
			};
			
			/// <summary>Advances the enumerator to the next <see cref="FieldDefinition"/> of the <see cref="FeatureDefinition"/>.</summary>
			virtual bool MoveNext();
			
			/// <summary>Sets the enumerator to its initial position, which is before the first <see cref="FieldDefinition"/> in the <see cref="FeatureDefinition"/>.</summary>
			virtual void Reset();
		};
	}
}
