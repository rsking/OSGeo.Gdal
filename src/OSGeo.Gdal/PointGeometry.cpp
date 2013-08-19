#include "StdAfx.h"
#include "PointGeometry.h"
#include "Geometry.h"

using namespace OSGeo::Ogr;

PointGeometry::PointGeometry(OGRPoint* point) : Geometry(point)
{
	this->_point = point;
}

PointGeometry::PointGeometry(double x, double y, double z) : Geometry(NULL)
{
	this->_point = NULL;
	this->_x = x;
	this->_y = y;
	this->_z = z;
}

double PointGeometry::X::get()
{
	return this->_point == NULL ? this->_x : this->_point->getX();
}

void PointGeometry::X::set(double value)
{
	this->_point == NULL ? this->_x = value : this->_point->setX(value);
}

double PointGeometry::Y::get()
{
	return this->_point == NULL ? this->_y : this->_point->getY();
}

void PointGeometry::Y::set(double value)
{
	this->_point == NULL ? this->_y = value : this->_point->setY(value);
}

double PointGeometry::Z::get()
{
	return this->_point == NULL ? this->_z : this->_point->getZ();
}

void PointGeometry::Z::set(double value)
{
	this->_point == NULL ? this->_z = value : this->_point->setZ(value);
}
