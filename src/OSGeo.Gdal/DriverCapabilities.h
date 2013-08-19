
#pragma once

namespace OSGeo 
{
	namespace Ogr
	{
		/// <summary>The driver capabilities.</summary>
		[System::Flags]
		public enum class DriverCapabilities : int
		{
			/// <summary>The driver has no specific capabilities.</summary>
			None = 0,

			/// <summary>The driver can create data sources.</summary>
			CreateDataSource = 1,

			/// <summary>The driver can delete data sources.</summary>
			DeleteDataSource = 2
		};
	}
}