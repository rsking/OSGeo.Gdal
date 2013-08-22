#include "StdAfx.h"
#include "Geometry.h"
#include "GeometryCollection.h"
#include "Point.h"
#include "Polygon.h"
#include "LineString.h"
#include "MultiPolygon.h"
#include "MultiPoint.h"
#include "MultiLineString.h"
#include "SpatialReference.h"

using namespace System;
using namespace OSGeo::Ogr;

Geometry::Geometry(OGRGeometry* geometry)
{
	this->_geometry = geometry;
}

Geometry^ Geometry::FromGeometry(OGRGeometry* geometry)
{
	if (geometry != NULL)
	{
		OGRwkbGeometryType geomType = geometry->getGeometryType();

		switch (geomType)
		{
		case wkbPoint:
		case wkbPoint25D:
			return gcnew OSGeo::Ogr::Point((OGRPoint*)geometry);
		case wkbLineString:
		case wkbLineString25D:
			return gcnew OSGeo::Ogr::LineString((OGRLineString*)geometry);
		case wkbPolygon:
		case wkbPolygon25D:
			return gcnew OSGeo::Ogr::Polygon((OGRPolygon*)geometry);
		case wkbMultiPoint:
		case wkbMultiPoint25D:
			return gcnew OSGeo::Ogr::MultiPoint((OGRMultiPoint*)geometry);
		case wkbMultiLineString:
		case wkbMultiLineString25D:
			return gcnew OSGeo::Ogr::MultiLineString((OGRMultiLineString*)geometry);
		case wkbMultiPolygon:
		case wkbMultiPolygon25D:
			return gcnew OSGeo::Ogr::MultiPolygon((OGRMultiPolygon*)geometry);
		case wkbGeometryCollection:
		case wkbGeometryCollection25D:
			return gcnew OSGeo::Ogr::GeometryCollection((OGRGeometryCollection*)geometry);
		}
	}

	return nullptr;
}

Geometry^ Geometry::FromWkb(array<unsigned char, 1>^ wkb)
{
	OGRGeometry* geometry;
	pin_ptr<unsigned char> pointer = &wkb[0];
	OGRGeometryFactory::createFromWkb(pointer, NULL, &geometry, wkb->Length);
	return Geometry::FromGeometry(geometry);
}

Geometry^ Geometry::FromText(String^ text)
{
	return Geometry::FromText(text, OSGeo::Ogr::GeometryTextFormat::Wkt);
}

Geometry^ Geometry::FromText(String^ text, GeometryTextFormat format)
{
	OGRGeometry* geometry;
	IntPtr pointer = Runtime::InteropServices::Marshal::StringToHGlobalAnsi(text);
	char* charArray = (char*)(void*)pointer;

	switch (format)
	{
	case OSGeo::Ogr::GeometryTextFormat::Wkt:
		OGRGeometryFactory::createFromWkt(&charArray, NULL, &geometry);
		break;
	case OSGeo::Ogr::GeometryTextFormat::Gml:
		geometry = OGRGeometryFactory::createFromGML(charArray);
		break;
	default:
		throw gcnew Exception("");
	}

	Runtime::InteropServices::Marshal::FreeHGlobal(pointer);
	return Geometry::FromGeometry(geometry);
}

Geometry^ Geometry::Clone()
{
	return Geometry::FromGeometry(this->_geometry->clone());
}

void Geometry::Empty()
{
	this->_geometry->empty();
}

bool Geometry::Equals(Geometry^ geometry)
{
	return this->_geometry->Equals(geometry->_geometry) != NULL;
}

void Geometry::CloseRings()
{
	this->_geometry->closeRings();
}

void Geometry::Segmentize(double maxLength)
{
	this->_geometry->segmentize(maxLength);
}

bool Geometry::Intersects(Geometry^ geometry)
{
	return this->_geometry->Intersects(geometry->_geometry) != FALSE;
}

bool Geometry::Disjoint(Geometry^ geometry)
{
	return this->_geometry->Disjoint(geometry->_geometry) != FALSE;
}

bool Geometry::Touches(Geometry^ geometry)
{
	return this->_geometry->Touches(geometry->_geometry) != FALSE;
}

bool Geometry::Crosses(Geometry^ geometry)
{
	return this->_geometry->Crosses(geometry->_geometry) != FALSE;
}

bool Geometry::Within(Geometry^ geometry)
{
	return this->_geometry->Within(geometry->_geometry) != FALSE;
}

bool Geometry::Contains(Geometry^ geometry)
{
	return this->_geometry->Contains(geometry->_geometry) != FALSE;
}

bool Geometry::Overlaps(Geometry^ geometry)
{
	return this->_geometry->Overlaps(geometry->_geometry) != FALSE;
}

OGRGeometry* Geometry::Handle::get()
{
	return this->_geometry;
}

SpatialReference^ Geometry::SpatialReference::get()
{
	return this->_srs == nullptr ? this->_srs = OSGeo::Ogr::SpatialReference::FromOGRSpatialReference(this->_geometry->getSpatialReference()) : this->_srs;
}

void Geometry::SpatialReference::set(OSGeo::Ogr::SpatialReference^ value)
{
	this->_geometry->assignSpatialReference(value->Handle);
	this->_srs = value;
}

int Geometry::Dimensions::get()
{
	return this->_geometry->getDimension();
}

int Geometry::CoordinateDimensions::get()
{
	return this->_geometry->getCoordinateDimension();
}

void Geometry::CoordinateDimensions::set(int value)
{
	return this->_geometry->setCoordinateDimension(value);
}

bool Geometry::IsEmpty::get()
{
	return this->_geometry->IsEmpty() != FALSE;
}

bool Geometry::IsValid::get()
{
	return this->_geometry->IsValid() != FALSE;
}

bool Geometry::IsSimple::get()
{
	return this->_geometry->IsSimple() != FALSE;
}

bool Geometry::IsRing::get()
{
	return this->_geometry->IsRing() != FALSE;
}

String^ Geometry::ToString()
{
	return this->ToString(OSGeo::Ogr::GeometryTextFormat::Wkt);
}

String^ Geometry::ToString(GeometryTextFormat format)
{
	char* wkt;
	switch (format)
	{
	case OSGeo::Ogr::GeometryTextFormat::Wkt:
		this->_geometry->exportToWkt(&wkt);
		break;
	case OSGeo::Ogr::GeometryTextFormat::Gml:
		wkt = this->_geometry->exportToGML();
		break;
	case OSGeo::Ogr::GeometryTextFormat::Kml:
		wkt = this->_geometry->exportToKML();
		break;
	case OSGeo::Ogr::GeometryTextFormat::Json:
		wkt = this->_geometry->exportToJson();
		break;
	}

	String^ value = gcnew String(wkt);
	OGRFree(wkt);
	return value;
}

array<Byte>^ Geometry::ToBinary()
{
	// initialise the variables
	int size = this->_geometry->WkbSize();
	unsigned char* wkb = new unsigned char[size];

	// export the value, using the byte order of the platform
	this->_geometry->exportToWkb(BitConverter::IsLittleEndian ? wkbNDR : wkbXDR, wkb);

	// copy this to the return array
	array<unsigned char, 1>^ value = gcnew array<unsigned char>(size);
	Runtime::InteropServices::Marshal::Copy((IntPtr)wkb, value, 0, size);

	// free the memory
	delete[] wkb;

	// return the array
	return value;
}