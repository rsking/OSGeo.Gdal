#include "StdAfx.h"
#include "PointGeometry.h"
#include "PointGeometryEnumerator.h"

using namespace System;
using namespace OSGeo::Ogr;

PointGeometryEnumerator::PointGeometryEnumerator(OGRLineString* lineString)
{
	this->_lineString = lineString;
	this->_currentIndex = -1;
}

PointGeometry^ PointGeometryEnumerator::Current::get()
{
	return this->_currentPoint;
}

Object^ PointGeometryEnumerator::CurrentBase::get()
{
	return this->Current;
}

bool PointGeometryEnumerator::MoveNext()
{
	this->_currentIndex++;
	if (this->_currentIndex < this->_lineString->getNumPoints())
	{
		OGRPoint* point = new OGRPoint();
		this->_lineString->getPoint(this->_currentIndex, point);
		this->_currentPoint = gcnew PointGeometry(point);
		return true;
	}

	return false;
}

void PointGeometryEnumerator::Reset()
{
	this->_currentIndex = -1;
}

PointGeometryEnumerator::~PointGeometryEnumerator()
{
	// make sure we clear the last current layer
	this->_currentPoint = nullptr;
}
