
#pragma once

namespace OSGeo 
{
	namespace Ogr
	{
		[System::Flags]
		public enum class DriverCapabilities : int
		{

			None = 0,
			CreateDataSource = 1,
			DeleteDataSource = 2
		};
	}
}