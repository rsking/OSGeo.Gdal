#include "StdAfx.h"
#include "Point.h"
#include "Geometry.h"

using namespace OSGeo::Ogr;

Point::Point(OGRPoint* point) : Geometry(point)
{
	this->_point = point;
}

Point::Point() : Geometry(this->_point = new OGRPoint())
{
}

Point::Point(double x, double y) : Geometry(this->_point = new OGRPoint(x, y))
{
}

Point::Point(double x, double y, double z) : Geometry(this->_point = new OGRPoint(x, y, z))
{
}

double Point::X::get()
{
	return this->_point->getX();
}

void Point::X::set(double value)
{
	this->_point->setX(value);
}

double Point::Y::get()
{
	return this->_point->getY();
}

void Point::Y::set(double value)
{
	this->_point->setY(value);
}

double Point::Z::get()
{
	return this->_point->getZ();
}

void Point::Z::set(double value)
{
	this->_point->setZ(value);
}
