#include "StdAfx.h"
#include "Curve.h"
#include "PointGeometry.h"

using namespace OSGeo::Ogr;

Curve::Curve()
{
}

Curve::Curve(OGRCurve* curve) : Geometry(curve)
{
	this->_curve = curve;
}

void Curve::SetGeometryObject(OGRGeometry* geometry)
{
	this->_curve = (OGRCurve*)geometry;
	Geometry::SetGeometryObject(geometry);
}

double Curve::Length::get()
{
	return this->_curve->get_Length();
}

PointGeometry^ Curve::Start::get()
{
	OGRPoint* point = new OGRPoint();
	this->_curve->StartPoint(point);
	return gcnew PointGeometry(point);
}

PointGeometry^ Curve::End::get()
{
	OGRPoint* point = new OGRPoint();
	this->_curve->EndPoint(point);
	return gcnew PointGeometry(point);
}

bool Curve::IsClosed::get()
{
	return this->_curve->get_IsClosed() != 0;
}

PointGeometry^ Curve::GetPoint(double distance)
{
	OGRPoint* point = new OGRPoint();
	this->_curve->Value(distance, point);
	return gcnew PointGeometry(point);
}
