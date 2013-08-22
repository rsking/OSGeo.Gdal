#include "StdAfx.h"
#include "Curve.h"
#include "Point.h"

using namespace OSGeo::Ogr;

Curve::Curve(OGRCurve* curve) : Geometry(curve)
{
	this->_curve = curve;
}

double Curve::Length::get()
{
	return this->_curve->get_Length();
}

Point^ Curve::Start::get()
{
	OGRPoint* point = new OGRPoint();
	this->_curve->StartPoint(point);
	return gcnew Point(point);
}

Point^ Curve::End::get()
{
	OGRPoint* point = new OGRPoint();
	this->_curve->EndPoint(point);
	return gcnew Point(point);
}

bool Curve::IsClosed::get()
{
	return this->_curve->get_IsClosed() != 0;
}

Point^ Curve::GetPoint(double distance)
{
	OGRPoint* point = new OGRPoint();
	this->_curve->Value(distance, point);
	return gcnew Point(point);
}
