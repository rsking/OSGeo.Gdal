#include "StdAfx.h"
#include "LineString.h"
#include "PointGeometry.h"
#include "PointGeometryEnumerator.h"

using namespace OSGeo::Ogr;

LineString::LineString(void)
{
	this->_lineString = new OGRLineString();
	Curve::SetGeometryObject(this->_lineString);
}

LineString::LineString(OGRLineString* lineString) : Curve(lineString)
{
	this->_lineString = lineString;
}

System::Collections::Generic::IEnumerator<OSGeo::Ogr::PointGeometry^>^ LineString::GetEnumerator()
{
	return gcnew PointGeometryEnumerator(this->_lineString);
}

IEnumerator^ LineString::GetEnumeratorBase()
{
	return gcnew PointGeometryEnumerator(this->_lineString);
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

void LineString::Add(PointGeometry^ point)
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

bool LineString::Contains(PointGeometry^ point)
{
	return false;
}

void LineString::CopyTo(array<PointGeometry^>^ destination, int index)
{
	int count = this->_lineString->getNumPoints();
	OGRRawPoint* points = new OGRRawPoint[count];
	double* z = new double[count];
	this->_lineString->getPoints(points, z);

	for (int i = 0; i < count; i++)
	{
		destination[index + i] = gcnew PointGeometry(points[i].x, points[i].y, z[i]);
	}
}

bool LineString::Remove(PointGeometry^ point)
{
	return false;
}

void LineString::RemoveAt(int index)
{
}

OSGeo::Ogr::PointGeometry^ LineString::Points::get(int index) 
{
	OGRPoint* point = NULL;
	this->_lineString->getPoint(index, point);
	return gcnew PointGeometry(point);
}

void LineString::Points::set(int index, OSGeo::Ogr::PointGeometry^ value) 
{
	this->_lineString->setPoint(index, (OGRPoint*)value->Handle);
}

int LineString::IndexOf(PointGeometry^ point)
{
	return -1;
}

void LineString::Insert(int index, PointGeometry^ point)
{
}
