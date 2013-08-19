#include "StdAfx.h"
#include "Surface.h"
#include "Geometry.h"

using namespace OSGeo::Ogr;

Surface::Surface() : Geometry()
{
}

Surface::Surface(OGRSurface* surface) : Geometry(surface)
{
	this->_surface = surface;
}

double Surface::Area::get()
{
	return this->_surface->get_Area();
}
