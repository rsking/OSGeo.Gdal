#include "StdAfx.h"
#include "LinearRing.h"

using namespace OSGeo::Ogr;

LinearRing::LinearRing(OGRLinearRing* linearRing) : LineString(linearRing)
{
	this->_linearRing = linearRing;
}

bool LinearRing::IsClockwise::get()
{
	return this->_linearRing->isClockwise() != 0;
}
