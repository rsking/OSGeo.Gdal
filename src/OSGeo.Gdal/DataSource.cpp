#include "Stdafx.h"
#include <msclr/marshal.h>
#include <ogrsf_frmts.h> 
#include "Driver.h"
#include "DataSource.h"
#include "LayerCollection.h"

using namespace System;
using namespace OSGeo::Ogr;

DataSource::DataSource(OGRDataSource* dataSource)
{
	this->_dataSource = dataSource;
	this->_driver = gcnew OSGeo::Ogr::Driver(this->_dataSource->GetDriver());
}

DataSource::DataSource(OGRDataSource* dataSource, OGRSFDriver* driver)
{
	this->_dataSource = dataSource;
	this->_driver = gcnew OSGeo::Ogr::Driver(driver);
}

DataSource^ DataSource::Open(String^ filename)
{
	OGRRegisterAll();
	msclr::interop::marshal_context cxt;
	OGRDataSource *poDS;
	char const* input = cxt.marshal_as<char const*>(filename);
	poDS = OGRSFDriverRegistrar::Open(input, FALSE);
	return gcnew OSGeo::Ogr::DataSource(poDS);
}

DataSource^ DataSource::Copy(String^ name)
{
	OGRRegisterAll();
	msclr::interop::marshal_context cxt;
	return gcnew OSGeo::Ogr::DataSource(this->_driver->Handle->CopyDataSource(this->Handle, cxt.marshal_as<char const*>(name), NULL), this->_driver->Handle);
}

OSGeo::Ogr::Driver^ DataSource::Driver::get()
{
	return this->_driver;
}

OGRDataSource* DataSource::Handle::get()
{
	return this->_dataSource;
}

String^ DataSource::Name::get()
{
	const char* name = this->_dataSource->GetName();
	msclr::interop::marshal_context cxt;
	return cxt.marshal_as<String^>(name);
}

LayerCollection^ DataSource::Layers::get()
{
	return gcnew LayerCollection(this->_dataSource);
}

DataSource::!DataSource()
{
	if (this->_dataSource != NULL)
	{
		OGRDataSource::DestroyDataSource(this->_dataSource);
		this->_dataSource = NULL;
	}
}

DataSource::~DataSource()
{
	this->!DataSource();
}