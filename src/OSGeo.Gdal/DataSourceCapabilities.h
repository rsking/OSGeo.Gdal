#pragma once

namespace OSGeo 
{
	namespace Ogr
	{
		/// <summary>The data source capabilities.</summary>
		[System::Flags]
		public enum class DataSourceCapabilities : int
		{
			/// <summary>The data source has no specific capabilities.</summary>
			None = 0,

			/// <summary>The data source can create new layers.</summary>
			CreateLayer = 1,
			
			/// <summary>The data source can delete layers.</summary>
			DeleteLayer = 2
		};
	}
}