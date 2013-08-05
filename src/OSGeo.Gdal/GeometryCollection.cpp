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
	return gcnew GeometryEnumerator(this->_geometryCollection);
}

IEnumerator^ GeometryCollection::GetEnumeratorBase()
{
	return gcnew GeometryEnumerator(this->_geometryCollection);
}

GeometryEnumerator::GeometryEnumerator(OGRGeometryCollection* geometryCollection)
{
	this->_geometryCollection = geometryCollection;
}

Geometry^ GeometryEnumerator::Current::get()
{
	return this->_currentGeometry;
}

Object^ GeometryEnumerator::CurrentBase::get()
{
	return this->Current;
}

bool GeometryEnumerator::MoveNext()
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

void GeometryEnumerator::Reset()
{
	this->ReleaseCurrentGeometry();
	_currentIndex = -1;
}

GeometryEnumerator::~GeometryEnumerator()
{
	// make sure we clear the current Geometry
	this->ReleaseCurrentGeometry();
}

void GeometryEnumerator::ReleaseCurrentGeometry()
{
	if (this->_currentGeometry != nullptr)
	{
		this->_currentGeometry->~Geometry();
		this->_currentGeometry = nullptr;
	}
}