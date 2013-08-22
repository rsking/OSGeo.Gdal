#include "StdAfx.h"
#include "LineString.h"
#include "Point.h"

using namespace OSGeo::Ogr;

LineString::LineString(void) : Curve(this->_lineString = new OGRLineString())
{
}

LineString::LineString(OGRLineString* lineString) : Curve(lineString)
{
	this->_lineString = lineString;
}

System::Collections::Generic::IEnumerator<OSGeo::Ogr::Point^>^ LineString::GetEnumerator()
{
	return gcnew Enumerator(this->_lineString);
}

IEnumerator^ LineString::GetEnumeratorBase()
{
	return gcnew Enumerator(this->_lineString);
}

int LineString::Count::get()
{
	return this->_lineString->getNumPoints();
}

void LineString::Count::set(int value)
{
	this->_lineString->setNumPoints(value);
}

bool LineString::IsReadOnly::get()
{
	return false;
}

void LineString::Add(Point^ point)
{
	return this->_lineString->addPoint(point->X, point->Y, point->Z);
}

void LineString::Add(LineString^ lineString)
{
	this->Add(lineString, 0, lineString->Count);
}

void LineString::Add(LineString^ lineString, int start, int length)
{
	this->_lineString->addSubLineString((OGRLineString*)lineString->Handle, start, start + length - 1);
}

void LineString::Clear()
{
	this->_lineString->empty();
}

bool LineString::Contains(Point^ point)
{
	return false;
}

void LineString::CopyTo(array<Point^>^ destination, int index)
{
	int count = this->_lineString->getNumPoints();
	OGRRawPoint* points = new OGRRawPoint[count];
	double* z = new double[count];
	this->_lineString->getPoints(points, z);

	for (int i = 0; i < count; i++)
	{
		destination[index + i] = gcnew Point(points[i].x, points[i].y, z[i]);
	}
}

bool LineString::Remove(Point^ point)
{
	return false;
}

void LineString::RemoveAt(int index)
{
}

OSGeo::Ogr::Point^ LineString::Points::get(int index) 
{
	OGRPoint* point = NULL;
	this->_lineString->getPoint(index, point);
	return gcnew Point(point);
}

void LineString::Points::set(int index, OSGeo::Ogr::Point^ value) 
{
	this->_lineString->setPoint(index, (OGRPoint*)value->Handle);
}

int LineString::IndexOf(Point^ point)
{
	return -1;
}

void LineString::Insert(int index, Point^ point)
{
}

LineString::Enumerator::Enumerator(OGRLineString* lineString)
{
	this->_lineString = lineString;
	this->_currentIndex = -1;
}

Point^ LineString::Enumerator::Current::get()
{
	return this->_currentPoint;
}

System::Object^ LineString::Enumerator::CurrentBase::get()
{
	return this->Current;
}

bool LineString::Enumerator::MoveNext()
{
	this->_currentIndex++;
	if (this->_currentIndex < this->_lineString->getNumPoints())
	{
		OGRPoint* point = new OGRPoint();
		this->_lineString->getPoint(this->_currentIndex, point);
		this->_currentPoint = gcnew Point(point);
		return true;
	}

	return false;
}

void LineString::Enumerator::Reset()
{
	this->_currentIndex = -1;
}

LineString::Enumerator::~Enumerator()
{
	// make sure we clear the last current layer
	this->_currentPoint = nullptr;
}
