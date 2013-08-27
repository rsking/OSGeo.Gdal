#include "Stdafx.h"
#include <msclr/marshal.h>
#include "DataSource.h"
#include "Driver.h"
#include "GdalException.h"

using namespace OSGeo::Ogr;

Driver::Driver(OGRSFDriver* driver)
{
	this->_driver = driver;

	// get the capabilities
	this->_capabilities = DriverCapabilities::None;
	if (this->_driver->TestCapability(ODrCCreateDataSource))
	{
		this->_capabilities = this->_capabilities | DriverCapabilities::CreateDataSource;
	}

	if (this->_driver->TestCapability(ODrCDeleteDataSource))
	{
		this->_capabilities = this->_capabilities | DriverCapabilities::DeleteDataSource;
	}
}

DataSource^ Driver::Open(String^ name)
{
	OGRRegisterAll();
	msclr::interop::marshal_context cxt;
	OGRDataSource *poDS;
	char const* input = cxt.marshal_as<char const*>(name);
	poDS = this->_driver->Open(input, FALSE);
	poDS->SetDriver(this->_driver);
	return gcnew OSGeo::Ogr::DataSource(poDS);
}

DataSource^ Driver::CreateDataSource(String^ name)
{
	OGRRegisterAll();
	msclr::interop::marshal_context cxt;
	OGRDataSource *poDS;
	char const* input = cxt.marshal_as<char const*>(name);
	poDS = this->_driver->CreateDataSource(input, NULL);
	return gcnew OSGeo::Ogr::DataSource(poDS);
}

DataSource^ Driver::CopyDataSource(DataSource sourceDataSource, String^ name, String^ options)
{
	OGRRegisterAll();
	msclr::interop::marshal_context cxt;
	OGRDataSource *poDS;
	char const* input = cxt.marshal_as<char const*>(name);
	poDS = this->_driver->CopyDataSource(sourceDataSource.Handle, input, NULL);
	return gcnew OSGeo::Ogr::DataSource(poDS, this->_driver);
}

void Driver::DeleteDataSource(String^ name)
{
	msclr::interop::marshal_context cxt;
	char const* input = cxt.marshal_as<char const*>(name);
	OGRErr errorValue = this->_driver->DeleteDataSource(input);
	if (errorValue != OGRERR_NONE)
	{
		throw OSGeo::GdalException::Create(errorValue);
	}
}

Driver^ Driver::FromName(String^ name)
{
	OGRRegisterAll();
	msclr::interop::marshal_context cxt;
	OGRSFDriver *poDr;
	char const* input = cxt.marshal_as<char const*>(name);
	OGRSFDriverRegistrar* registrar = OGRSFDriverRegistrar::GetRegistrar();
	poDr = registrar->GetDriverByName(input);
	return gcnew OSGeo::Ogr::Driver(poDr);
}

String^ Driver::Name::get()
{
	const char* name = this->_driver->GetName();
	return msclr::interop::marshal_as<String^>(name);
}

OGRSFDriver* Driver::Handle::get()
{
	return this->_driver;
}

DriverCapabilities Driver::Capabilities::get()
{
	return this->_capabilities;
}

System::String^ Driver::ToString()
{
	return this->Name;
}