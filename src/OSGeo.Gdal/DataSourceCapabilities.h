#pragma once

namespace OSGeo 
{
	namespace Ogr
	{
		[System::Flags]
		public enum class DataSourceCapabilities : int
		{
			None = 0,
			CreateLayer = 1,
			DeleteLayer = 2
		};
	}
}