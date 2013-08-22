#include "StdAfx.h"
#include "GeometryCollection.h"
#include "Geometry.h"

using namespace System;
using namespace OSGeo::Ogr;

GeometryCollection::GeometryCollection(OGRGeometryCollection* geometryCollection) : Geometry(geometryCollection)
{
	this->_geometryCollection = geometryCollection;
}

int GeometryCollection::Count::get()
{
	return this->_geometryCollection->getNumGeometries();
}

Generic::IEnumerator<Geometry^>^ GeometryCollection::GetEnumerator()
{
	return gcnew Enumerator(this->_geometryCollection);
}

IEnumerator^ GeometryCollection::GetEnumeratorBase()
{
	return gcnew Enumerator(this->_geometryCollection);
}

GeometryCollection::Enumerator::Enumerator(OGRGeometryCollection* geometryCollection)
{
	this->_geometryCollection = geometryCollection;
	this->Reset();
}

Geometry^ GeometryCollection::Enumerator::Current::get()
{
	return this->_currentGeometry;
}

Object^ GeometryCollection::Enumerator::CurrentBase::get()
{
	return this->Current;
}

bool GeometryCollection::Enumerator::MoveNext()
{
	this->ReleaseCurrentGeometry();
	_currentIndex++;

	if (this->_currentIndex < this->_geometryCollection->getNumGeometries())
	{
		OGRGeometry* geometry = this->_geometryCollection->getGeometryRef(this->_currentIndex);
		if (geometry != NULL)
		{
			this->_currentGeometry = Geometry::FromGeometry(geometry);
			return true;
		}
	}

	return false;
}

void GeometryCollection::Enumerator::Reset()
{
	this->ReleaseCurrentGeometry();
	_currentIndex = -1;
}

GeometryCollection::Enumerator::~Enumerator()
{
	// make sure we clear the current Geometry
	this->ReleaseCurrentGeometry();
}

void GeometryCollection::Enumerator::ReleaseCurrentGeometry()
{
	if (this->_currentGeometry != nullptr)
	{
		this->_currentGeometry->~Geometry();
		this->_currentGeometry = nullptr;
	}
}