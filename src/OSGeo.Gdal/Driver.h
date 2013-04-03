#pragma once

#include <ogrsf_frmts.h>
#include "DriverCapabilities.h"

using namespace System;

namespace OSGeo 
{
	namespace Ogr
	{
		ref class DataSource;

		public ref class Driver
		{
		private:
			/// <summary>The GDAL driver object.</summary>
			OGRSFDriver* _driver;

			DriverCapabilities _capabilities;
		internal:
			/// <summary>Initialises a new instance of the <see cref="Driver" /> class using the specified driver object.Driver</summary>
			Driver(OGRSFDriver* driver);

			property OGRSFDriver* Handle 
			{ 
				OGRSFDriver* get();
			}
		public:
			/// <summary>Get a driver using the specified name.</summary>
			static Driver^ FromName(String^ name);

			/// <summary>Attempt to open file with this driver.</summary>
			DataSource^ Open(String^ name);

			/// <summary>This method attempts to create a new data source based on the passed driver.</summary>
			DataSource^ CreateDataSource(String^ name);

			/// <summary>This method creates a new datasource by copying all the layers from the source datasource.</summary>
			DataSource^ CopyDataSource(DataSource sourceDataSource, String^ name, String^ options); 

			/// <summary>Delete a datasource.</summary>
			void DeleteDataSource(String^ name);

			/// <summary>Gets the name of the driver.</summary>
			property String^ Name
			{
				String^ get();
			}

			property DriverCapabilities Capabilities
			{
				DriverCapabilities get();
			}
		};
	}
}

