#pragma once

namespace OSGeo 
{
	namespace Ogr
	{
		ref class Layer;

		/// <summary>The <see cref="Layer"/> capabilities.</summary>
		[System::Flags]
		public enum class LayerCapabilities : int
		{
			/// <summary>No specific capabilities.</summary>
			None = 0x00,

			/// <summary>Supports random reading.</summary>
			RandomRead = 0x01,

			/// <summary>Supports sequential writes.</summary>
			SequentialWrite = 0x02,

			/// <summary>Supports random writes.</summary>
			RandomWrite = 0x04,

			/// <summary>Supports fast spatial filtering.</summary>
			FastSpatialFilter = 0x08,

			/// <summary>Supports fast feature counting.</summary>
			FastFeatureCount = 0x10,

			/// <summary>Supports fast extents.</summary>
			FastGetExtent = 0x20,

			/// <summary>Can create a field.</summary>
			CreateField = 0x40,

			/// <summary>Can delete a field.</summary>
			DeleteField = 0x80,

			/// <summary>Can reorder fields.</summary>
			ReorderFields = 0x100,

			/// <summary>Can alter a field definition.</summary>
			AlterFieldDefn = 0x200,

			/// <summary>Supports transactions.</summary>
			Transactions = 0x400,

			/// <summary>Can delete a feature,</summary>
			DeleteFeature = 0x800,

			/// <summary>Supports fast index setting.</summary>
			FastSetNextByIndex = 0x1000,

			/// <summary>Returns string as <see cref="System::Text::Encoding::UTF8"/>.</summary>
			StringsAsUTF8 = 0x2000,

			/// <summary>Can ignore fields.</summary>
			IgnoreFields = 0x4000
		};
	}
}