#include "StdAfx.h"
#include "GeometryCollection.h"
#include "Geometry.h"

using namespace System;
using namespace OSGeo::Ogr;

GeometryCollection::GeometryCollection(OGRGeometry* geometry)
{
	this->_geometry = geometry;
}

int GeometryCollection::Count::get()
{
	return this->_geometry;
}

Generic::IEnumerator<Geometry^>^ GeometryCollection::GetEnumerator()
{
	return gcnew GeometryEnumerator(this->_geometry);
}

IEnumerator^ GeometryCollection::GetEnumeratorBase()
{
	return gcnew GeometryEnumerator(this->_geometry);
}

GeometryEnumerator::GeometryEnumerator(OGRLayer* layer)
{
	this->_geometry = geometry;
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
	OGRGeometry* Geometry = this->_geometry->GetNextGeometry();
	if (Geometry != NULL)
	{
		this->_currentGeometry = gcnew Geometry(Geometry);
		return true;
	}

	return false;
}

void GeometryEnumerator::Reset()
{
	this->ReleaseCurrentGeometry();
	this->_layer->ResetReading();
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