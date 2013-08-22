#include "Stdafx.h"
#include "MultiLineString.h"

using namespace System;
using namespace OSGeo::Ogr;

MultiLineString::MultiLineString(OGRMultiLineString* multiLineString) : GeometryCollection(multiLineString)
{
	this->_multiLineString = multiLineString;
}

Generic::IEnumerator<LineString^>^ MultiLineString::GetEnumerator()
{
	return gcnew Enumerator(this->_multiLineString);
}

MultiLineString::Enumerator::Enumerator(OGRMultiLineString* multiLineString)
{
	this->_multiLineString = multiLineString;
	this->Reset();
}

LineString^ MultiLineString::Enumerator::Current::get()
{
	return (LineString^)this->_currentGeometry;
}

Object^ MultiLineString::Enumerator::CurrentBase::get()
{
	return this->Current;
}

bool MultiLineString::Enumerator::MoveNext()
{
	this->ReleaseCurrentGeometry();
	_currentIndex++;

	if (this->_currentIndex < this->_multiLineString->getNumGeometries())
	{
		OGRGeometry* geometry = this->_multiLineString->getGeometryRef(this->_currentIndex);
		if (geometry != NULL)
		{
			this->_currentGeometry = Geometry::FromGeometry(geometry);
			return true;
		}
	}

	return false;
}

void MultiLineString::Enumerator::Reset()
{
	this->ReleaseCurrentGeometry();
	_currentIndex = -1;
}

MultiLineString::Enumerator::~Enumerator()
{
	// make sure we clear the current Geometry
	this->ReleaseCurrentGeometry();
}

void MultiLineString::Enumerator::ReleaseCurrentGeometry()
{
	if (this->_currentGeometry != nullptr)
	{
		this->_currentGeometry->~Geometry();
		this->_currentGeometry = nullptr;
	}
}