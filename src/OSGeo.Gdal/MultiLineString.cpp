#include "Stdafx.h"
#include "LineString.h"
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

Generic::IEnumerator<Geometry^>^ MultiLineString::GetEnumeratorGeometry()
{
	return (Generic::IEnumerator<Geometry^>^)(gcnew Enumerator(this->_multiLineString));
}

MultiLineString::Enumerator::Enumerator(OGRMultiLineString* multiLineString)
{
	this->_multiLineString = multiLineString;
	this->Reset();
}

LineString^ MultiLineString::Enumerator::Current::get()
{
	return this->_currentLineString;
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
			this->_currentLineString = (LineString^)Geometry::FromGeometry(geometry);
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
	if (this->_currentLineString != nullptr)
	{
		this->_currentLineString->~LineString();
		this->_currentLineString = nullptr;
	}
}