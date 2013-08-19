#include "StdAfx.h"
#include "FeatureDefinition.h"
#include "FieldDefinitionCollection.h"

using namespace OSGeo::Ogr;

FeatureDefinition::FeatureDefinition(OGRFeatureDefn* featureDefinition)
{
	this->_featureDefinition = featureDefinition;
}

FieldDefinitionCollection^ FeatureDefinition::Fields::get()
{
	if (this->_fields == nullptr)
	{
		this->_fields = gcnew FieldDefinitionCollection(this->_featureDefinition);
	}

	return this->_fields;
}
