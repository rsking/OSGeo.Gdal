#include "Stdafx.h"
#include "MultiPoint.h"

using namespace System;
using namespace OSGeo::Ogr;

MultiPoint::MultiPoint(OGRMultiPoint* multiPoint) : GeometryCollection(multiPoint)
{
	this->_multiPoint = multiPoint;
}

Generic::IEnumerator<Point^>^ MultiPoint::GetEnumerator()
{
	return gcnew Enumerator(this->_multiPoint);
}

Generic::IEnumerator<Geometry^>^ MultiPoint::GetEnumeratorGeometry()
{
	return (Generic::IEnumerator<Geometry^>^)(gcnew Enumerator(this->_multiPoint));
}

MultiPoint::Enumerator::Enumerator(OGRMultiPoint* multiPoint)
{
	this->_multiPoint = multiPoint;
	this->Reset();
}

Point^ MultiPoint::Enumerator::Current::get()
{
	return (Point^)this->_currentGeometry;
}

Object^ MultiPoint::Enumerator::CurrentBase::get()
{
	return this->Current;
}

bool MultiPoint::Enumerator::MoveNext()
{
	this->ReleaseCurrentGeometry();
	_currentIndex++;

	if (this->_currentIndex < this->_multiPoint->getNumGeometries())
	{
		OGRGeometry* geometry = this->_multiPoint->getGeometryRef(this->_currentIndex);
		if (geometry != NULL)
		{
			this->_currentGeometry = Geometry::FromGeometry(geometry);
			return true;
		}
	}

	return false;
}

void MultiPoint::Enumerator::Reset()
{
	this->ReleaseCurrentGeometry();
	_currentIndex = -1;
}

MultiPoint::Enumerator::~Enumerator()
{
	// make sure we clear the current Geometry
	this->ReleaseCurrentGeometry();
}

void MultiPoint::Enumerator::ReleaseCurrentGeometry()
{
	if (this->_currentGeometry != nullptr)
	{
		this->_currentGeometry->~Geometry();
		this->_currentGeometry = nullptr;
	}
}