#include "Stdafx.h"
#include "MultiPoint.h"

using namespace System;
using namespace OSGeo::Ogr;

MultiPoint::MultiPoint(OGRMultiPoint* multiPoint) : GeometryCollection(multiPoint)
{
	this->_multiPoint = multiPoint;
}

double MultiPoint::Area::get()
{
	return this->_multiPoint->get_Area();
}

Generic::IEnumerator<Point^>^ MultiPoint::GetEnumerator()
{
	return gcnew PointEnumerator(this->_multiPoint);
}

MultiPoint::PointEnumerator::PointEnumerator(OGRMultiPoint* multiPoint)
{
	this->_multiPoint = multiPoint;
	this->Reset();
}

Point^ MultiPoint::PointEnumerator::Current::get()
{
	return (Point^)this->_currentGeometry;
}

Object^ MultiPoint::PointEnumerator::CurrentBase::get()
{
	return this->Current;
}

bool MultiPoint::PointEnumerator::MoveNext()
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

void MultiPoint::PointEnumerator::Reset()
{
	this->ReleaseCurrentGeometry();
	_currentIndex = -1;
}

MultiPoint::PointEnumerator::~PointEnumerator()
{
	// make sure we clear the current Geometry
	this->ReleaseCurrentGeometry();
}

void MultiPoint::PointEnumerator::ReleaseCurrentGeometry()
{
	if (this->_currentGeometry != nullptr)
	{
		this->_currentGeometry->~Geometry();
		this->_currentGeometry = nullptr;
	}
}