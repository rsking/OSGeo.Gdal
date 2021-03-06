#include "StdAfx.h"
#include "Polygon.h"
#include "Surface.h"
#include "LinearRing.h"

using namespace OSGeo::Ogr;

Polygon::Polygon(OGRPolygon* polygon) : Surface(polygon)
{
	this->_polygon = polygon;
}

Polygon::Polygon() : Surface(this->_polygon = new OGRPolygon())
{
}

Geometry^ Polygon::Clone()
{
	return gcnew Polygon((OGRPolygon*)this->_polygon->clone());
}

LinearRing^ Polygon::Outer::get()
{
	return gcnew LinearRing(this->_polygon->getExteriorRing());
}
