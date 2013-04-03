#pragma once

namespace OSGeo 
{
	namespace Ogr
	{
		[System::Flags]
		public enum class LayerCapabilities : int
		{
			None = 0x00,
			RandomRead = 0x01,
			SequentialWrite = 0x02,
			RandomWrite = 0x04,
			FastSpatialFilter = 0x08,
			FastFeatureCount = 0x10,
			FastGetExtent = 0x20,
			CreateField = 0x40,
			DeleteField = 0x80,
			ReorderFields = 0x100,
			AlterFieldDefn = 0x200,
			Transactions = 0x400,
			DeleteFeature = 0x800,
			FastSetNextByIndex = 0x1000,
			StringsAsUTF8 = 0x2000,
			IgnoreFields = 0x4000
		};
	}
}