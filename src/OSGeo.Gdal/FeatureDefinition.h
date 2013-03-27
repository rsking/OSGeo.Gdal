#pragma once

#include "FieldDefinitionCollection.h"

namespace OSGeo
{
	namespace Ogr
	{
		public ref class FeatureDefinition
		{
		private:
			FieldDefinitionCollection^ _fields;
			OGRFeatureDefn* _featureDefinition;
			~FeatureDefinition();
		protected:
			/// <summary></summary>
			!FeatureDefinition();
		internal:
			FeatureDefinition(OGRFeatureDefn* featureDefinition);
		public:
			property FieldDefinitionCollection^ Fields
			{
				FieldDefinitionCollection^ get();
			}
		};
	}
}

