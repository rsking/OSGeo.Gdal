#pragma once

#include "FieldDefinition.h"

using namespace System;
using namespace System::Collections;

namespace OSGeo 
{
	namespace Ogr
	{
		public ref class FieldDefinitionCollection : public Generic::IEnumerable<FieldDefinition^>
		{
		private:
			OGRFeatureDefn* _featureDefinition;
		internal:
			FieldDefinitionCollection(OGRFeatureDefn* featureDefinition);
		public:
			virtual Generic::IEnumerator<FieldDefinition^>^ GetEnumerator() sealed = Generic::IEnumerable<FieldDefinition^>::GetEnumerator;

			virtual IEnumerator^ GetEnumeratorBase() sealed = IEnumerable::GetEnumerator;

			property int Count
			{
				int get();
			}
		};

		private ref class FieldDefinitionEnumerator : public Generic::IEnumerator<FieldDefinition^>
		{
		private:
			int _currentIndex;
			OGRFieldDefn* _currentFieldDefinition;
			OGRFeatureDefn* _featureDefinition;
		public:
			FieldDefinitionEnumerator(OGRFeatureDefn* layer);
			property FieldDefinition^ Current { 
				virtual FieldDefinition^ get();
			};

			property Object^ CurrentBase { 
				virtual Object^ get() sealed = IEnumerator::Current::get;
			};

			virtual bool MoveNext();

			virtual void Reset();

			virtual ~FieldDefinitionEnumerator();
		};
	}
}
