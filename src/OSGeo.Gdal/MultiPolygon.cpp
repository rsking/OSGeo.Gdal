#include "Stdafx.h"
#include "MultiPolygon.h"

using namespace System;
using namespace OSGeo::Ogr;

MultiPolygon::MultiPolygon(OGRMultiPolygon* multiPolygon) : GeometryCollection(multiPolygon)
{
	this->_multiPolygon = multiPolygon;
}

double MultiPolygon::Area::get()
{
	return this->_multiPolygon->get_Area();
}

Generic::IEnumerator<Polygon^>^ MultiPolygon::GetEnumerator()
{
	return gcnew PolygonEnumerator(this->_multiPolygon);
}

PolygonEnumerator::PolygonEnumerator(OGRMultiPolygon* multiPolygon)
{
	this->_multiPolygon = multiPolygon;
	this->Reset();
}

Polygon^ PolygonEnumerator::Current::get()
{
	return (Polygon^)this->_currentGeometry;
}

Object^ PolygonEnumerator::CurrentBase::get()
{
	return this->Current;
}

bool PolygonEnumerator::MoveNext()
{
	this->ReleaseCurrentGeometry();
	_currentIndex++;

	if (this->_currentIndex < this->_multiPolygon->getNumGeometries())
	{
		OGRGeometry* geometry = this->_multiPolygon->getGeometryRef(this->_currentIndex);
		if (geometry != NULL)
		{
			this->_currentGeometry = Geometry::FromGeometry(geometry);
			return true;
		}
	}

	return false;
}

void PolygonEnumerator::Reset()
{
	this->ReleaseCurrentGeometry();
	_currentIndex = -1;
}

PolygonEnumerator::~PolygonEnumerator()
{
	// make sure we clear the current Geometry
	this->ReleaseCurrentGeometry();
}

void PolygonEnumerator::ReleaseCurrentGeometry()
{
	if (this->_currentGeometry != nullptr)
	{
		this->_currentGeometry->~Geometry();
		this->_currentGeometry = nullptr;
	}
}