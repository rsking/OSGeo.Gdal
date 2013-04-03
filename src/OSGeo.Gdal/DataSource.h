#pragma once

#include <ogrsf_frmts.h>
#include "DataSourceCapabilities.h"

using namespace System;

namespace OSGeo 
{
	namespace Ogr
	{
		ref class Driver;
		ref class LayerCollection;

		public ref class DataSource
		{
		private:
			/// <summary>The data source object.</summary>
			OGRDataSource* _dataSource;

			/// <summary>The driver.</summary>
			OSGeo::Ogr::Driver^ _driver;

			DataSourceCapabilities _capabilities;

			/// <summary></summary>
			~DataSource();
		protected:
			/// <summary></summary>
			!DataSource();
		internal:
			/// <summary>Initialises a new instance of the <see	cref="DataSource" /> class using the specified data source object.</summary>
			DataSource(OGRDataSource* dataSource);
			
			/// <summary>Initialises a new instance of the <see	cref="DataSource" /> class using the specified data source and driver objects.</summary>
			DataSource(OGRDataSource* dataSource, OGRSFDriver* driver);
			
			/// <summary>Gets the source pointer for this instance.</summary>
			property OGRDataSource* Handle
			{
				OGRDataSource* get();
			}
		public:
			/// <summary>Opens a data source using the specified name.</summary>
			static DataSource^ Open(String^ filename);

			/// <summary>Gets the driver for this instance.</summary>
			property OSGeo::Ogr::Driver^ Driver
			{
				OSGeo::Ogr::Driver^ get();
			}
			
			/// <summary>Gets the name of the dataset.</summary>
			property String^ Name
			{
				String^ get();
			}

			property DataSourceCapabilities Capabilities
			{
				DataSourceCapabilities get();
			}

			/// <summary>Gets the layers in the dataset.</summary>
			property OSGeo::Ogr::LayerCollection^ Layers
			{
				OSGeo::Ogr::LayerCollection^ get();
				//{
				//	return OSGeo::Ogr::LayerCollection::
				//	return nullptr; // gcnew OSGeo::Ogr::LayerCollection(this->_dataSource);
				//}
			}

			/// <summary>Copies this dataset to the specified name.</summary>
			DataSource^ Copy(String^ name);
		};
	}
}
