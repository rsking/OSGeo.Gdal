#pragma once

namespace OSGeo
{
	namespace Ogr
	{
		/// <summary>List of feature field types. This list is likely to be extended in the future ... avoid coding applications based on the assumption that all field types can be known.</summary>
		public enum class FieldType : int
		{
			/// <summary>Simple 32bit integer.</summary>
			Integer,

			/// <summary>List of 32bit integers.</summary>
			IntegerList,

			/// <summary>Double Precision floating point.</summary>
			Real,

			/// <summary>List of doubles.</summary>
			RealList,

			/// <summary>String of ASCII chars.</summary>
			String,

			/// <summary>Array of strings.</summary>
			StringList,

			/// <summary>Raw Binary data.</summary>
			Binary,

			/// <summary>Date.</summary>
			Date,

			/// <summary>Time.</summary>
			Time,

			/// <summary>Date and Time.</summary>
			DateTime
		};
	}
}