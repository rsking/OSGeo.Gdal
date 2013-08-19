#pragma once

#include "FieldDefinitionCollection.h"

namespace OSGeo
{
	namespace Ogr
	{
		/// <summary>Definition of a feature class or feature layer.</summary>
		public ref class FeatureDefinition sealed
		{
		private:
			/// <summary>The field definition collection.</summary>
			FieldDefinitionCollection^ _fields;

			/// <summary>The feature definition.</summary>
			OGRFeatureDefn* _featureDefinition;
		internal:
			/// <summary>Initialises a new instance of the <see cref="FeatureDefinition"/> class.</summary>
			FeatureDefinition(OGRFeatureDefn* featureDefinition);
		public:
			/// <summary>Gets the field definitions.</summary>
			property FieldDefinitionCollection^ Fields
			{
				FieldDefinitionCollection^ get();
			}
		};
	}
}

