#include "StdAfx.h"
#include <msclr/marshal.h>
#include "SpatialReference.h"
#include "GdalException.h"

using namespace System;
using namespace OSGeo::Ogr;

SpatialReference::SpatialReference(OGRSpatialReference* srs)
{
	this->_srs = srs;
}

SpatialReference::SpatialReference(System::String^ srs)
{
	msclr::interop::marshal_context ctx;
	const char* text = ctx.marshal_as<const char *>(srs);
	this->_srs = new OGRSpatialReference(text);
}

SpatialReference::~SpatialReference()
{
	if (this->_srs != NULL)
	{
		this->_srs->~OGRSpatialReference();
		this->_srs = NULL;
	}
}

SpatialReference^ SpatialReference::FromOGRSpatialReference(OGRSpatialReference* srs)
{
	if (srs != NULL)
	{
		return gcnew SpatialReference(srs);
	}

	return nullptr;
}

SpatialReference^ SpatialReference::FromEpsg(int epsg)
{
	OGRSpatialReference* srs = new OGRSpatialReference(NULL);
	OGRErr error =  srs->importFromEPSGA(epsg);
	if (error != OGRERR_NONE)
	{
		throw GdalException::Create(error);
	}

	return gcnew SpatialReference(srs);
}

SpatialReference^ SpatialReference::FromText(System::String^ text, SpatialReferenceImportFormat format)
{
	OGRSpatialReference* srs = new OGRSpatialReference(0);
	msclr::interop::marshal_context ctx;

	switch (format)
	{
	case OSGeo::Ogr::SpatialReferenceImportFormat::Wkt:
		{
			IntPtr pointer = Runtime::InteropServices::Marshal::StringToHGlobalAnsi(text);
			char* charArray = (char*)(void*)pointer;
			srs->importFromWkt(&charArray);
			Runtime::InteropServices::Marshal::FreeHGlobal(pointer);
		}

		break;
	case OSGeo::Ogr::SpatialReferenceImportFormat::Proj4:
		srs->importFromProj4(ctx.marshal_as<const char *>(text));
		break;
	case OSGeo::Ogr::SpatialReferenceImportFormat::Esri:
		{
			IntPtr pointer = Runtime::InteropServices::Marshal::StringToHGlobalAnsi(text);
			char* charArray = (char*)(void*)pointer;
			srs->importFromESRI(&charArray);
			Runtime::InteropServices::Marshal::FreeHGlobal(pointer);
		}

		break;
	case OSGeo::Ogr::SpatialReferenceImportFormat::Pci:
		srs->importFromPCI(ctx.marshal_as<const char *>(text));
		break;
	case OSGeo::Ogr::SpatialReferenceImportFormat::WmsAuto:
		srs->importFromWMSAUTO(ctx.marshal_as<const char *>(text));
		break;
	case OSGeo::Ogr::SpatialReferenceImportFormat::Xml:
		srs->importFromXML(ctx.marshal_as<const char *>(text));
		break;
	case OSGeo::Ogr::SpatialReferenceImportFormat::Urn:
		srs->importFromURN(ctx.marshal_as<const char *>(text));
		break;
	case OSGeo::Ogr::SpatialReferenceImportFormat::Url:
		srs->importFromUrl(ctx.marshal_as<const char *>(text));
		break;
	case OSGeo::Ogr::SpatialReferenceImportFormat::MapInfo:
		srs->importFromMICoordSys(ctx.marshal_as<const char *>(text));
		break;
	}
	
	return gcnew SpatialReference(srs);
}

int SpatialReference::Reference()
{
	return this->_srs->Reference();
}

int SpatialReference::Dereference()
{
	return this->_srs->Dereference();
}

void SpatialReference::Release()
{
	this->_srs->Release();
}

SpatialReference^ SpatialReference::Clone()
{
	return gcnew SpatialReference(this->_srs->Clone());
}

SpatialReference^ SpatialReference::CloneGeographic()
{
	return gcnew SpatialReference(this->_srs->CloneGeogCS());
}

OGRSpatialReference* SpatialReference::Handle::get()
{
	return this->_srs;
}

int SpatialReference::ReferenceCount::get()
{
	return this->_srs->GetReferenceCount();
}

String^ SpatialReference::ToString()
{
	return this->ToString(OSGeo::Ogr::SpatialReferenceExportFormat::Wkt);
}

bool SpatialReference::Equals(System::Object^ other)
{
	SpatialReference^ srs = dynamic_cast<SpatialReference^>(other);

	if (srs == nullptr)
	{
		return false;
	}

	return SpatialReference::Equals(srs);
}

bool SpatialReference::Equals(SpatialReference^ srs)
{
	return this->_srs->IsSame(srs->_srs) == TRUE;
}

String^ SpatialReference::ToString(SpatialReferenceExportFormat format)
{
	char* text;
	switch (format)
	{
	case OSGeo::Ogr::SpatialReferenceExportFormat::Wkt:
		this->_srs->exportToWkt(&text);
		break;
	case OSGeo::Ogr::SpatialReferenceExportFormat::PrettyWkt:
		this->_srs->exportToPrettyWkt(&text);
		break;
	case OSGeo::Ogr::SpatialReferenceExportFormat::Proj4:
		this->_srs->exportToProj4(&text);
		break;
	case OSGeo::Ogr::SpatialReferenceExportFormat::Xml:
		this->_srs->exportToXML(&text);
		break;
	case OSGeo::Ogr::SpatialReferenceExportFormat::MapInfo:
		this->_srs->exportToMICoordSys(&text);
		break;
	}

	String^ value = gcnew String(text);
	OGRFree(text);
	return value;
}
