#include "Stdafx.h"
#include <msclr/marshal.h>
#include "Feature.h"
#include "Geometry.h"
#include "StringMarshaller.h"

//using namespace OSGeo;
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

System::String^ Feature::GetString(int i)
{
	return StringMarshaller::GetStringAsUtf8(this->_feature->GetFieldAsString(i));
}