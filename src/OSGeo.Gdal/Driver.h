#pragma once

#include <ogrsf_frmts.h>
#include "DriverCapabilities.h"

using namespace System;

namespace OSGeo 
{
	namespace Ogr
	{
		ref class DataSource;

		/// <summary>Represents an operational format driver.</summary>
		public ref class Driver sealed
		{
		private:
			/// <summary>The GDAL driver object.</summary>
			OGRSFDriver* _driver;

			/// <summary>The driver capabilities.</summary>
			DriverCapabilities _capabilities;
		internal:
			/// <summary>Initialises a new instance of the <see cref="Driver" /> class using the specified driver object.Driver</summary>
			Driver(OGRSFDriver* driver);

			/// <summary>Gets the driver handle.</summary>
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

			/// <summary>This method creates a new data source by copying all the layers from the source data source.</summary>
			DataSource^ CopyDataSource(DataSource sourceDataSource, String^ name, String^ options); 

			/// <summary>Delete a data source.</summary>
			void DeleteDataSource(String^ name);

			/// <summary>Gets the name of the driver.</summary>
			property String^ Name
			{
				String^ get();
			}

			/// <summary>Gets the capabilities.</summary>
			property DriverCapabilities Capabilities
			{
				DriverCapabilities get();
			}
		};
	}
}

