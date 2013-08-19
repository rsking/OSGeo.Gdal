#pragma once

#include <ogr_feature.h>
#include "FieldType.h"

using namespace System;

namespace OSGeo
{
	namespace Ogr
	{
		/// <summary>Represents the field definition.</summary>
		public ref class FieldDefinition sealed
		{
		internal:
			/// <summary>The field definition object.</summary>
			OGRFieldDefn* _fieldDefinition;

			/// <summary>Initialises a new instance of the <see cref="FieldDefinition"/> class.</summary>
			/// <param name="fieldDefinition">The field definition.</param>
			FieldDefinition(OGRFieldDefn* fieldDefinition);
		public:
			/// <summary>Gets a human readable name for a field type.</summary>
			/// <param name="fieldType">The field type.</param>
			static String^ GetName(FieldType fieldType);

			/// <summary>Gets or sets the name of the field.</summary>
			property String^ Name
			{
				String^ get();
				void set(String^ value);
			}

			/// <summary>Gets or sets the field type.</summary>
			property FieldType Type
			{
				FieldType get();
				void set(FieldType value);
			}

			/// <summary>Converts this instance into a human-readable string value.</summary>
			virtual System::String^ ToString() override;
		};
	}
}

