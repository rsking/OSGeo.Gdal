#include "Stdafx.h"
#include "Feature.h"
#include "Geometry.h"

using namespace OSGeo::Ogr;

Feature::Feature(OGRFeature* feature)
{
	this->_feature = feature;
}

Geometry^ Feature::Geometry::get()
{
	return this->_geometry == nullptr ? this->_geometry = OSGeo::Ogr::Geometry::FromGeometry(this->_feature->GetGeometryRef()) : this->_geometry;
}

Feature::~Feature()
{
	this->!Feature();
}

Feature::!Feature()
{
	if (this->_feature != NULL)
	{
		OGRFeature::DestroyFeature(this->_feature);
		this->_feature = NULL;
	}
}