#include "StdAfx.h"
#include "Polygon.h"
#include "Surface.h"
#include "LinearRing.h"

using namespace OSGeo::Ogr;

Polygon::Polygon(OGRPolygon* polygon) : Surface(polygon)
{
	this->_polygon = polygon;
}

Polygon::Polygon()
{
	this->_polygon = new OGRPolygon();
	Surface::SetGeometryObject(this->_polygon);
}

Geometry^ Polygon::Clone()
{
	return gcnew Polygon((OGRPolygon*)this->_polygon->clone());
}

LinearRing^ Polygon::Outer::get()
{
	return gcnew LinearRing(this->_polygon->getExteriorRing());
}
