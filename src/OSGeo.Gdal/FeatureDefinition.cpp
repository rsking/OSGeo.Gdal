#include "StdAfx.h"
#include "FeatureDefinition.h"
#include "FieldDefinitionCollection.h"

using namespace OSGeo::Ogr;

FeatureDefinition::FeatureDefinition(OGRFeatureDefn* featureDefinition)
{
	this->_featureDefinition = featureDefinition;
}

FeatureDefinition::~FeatureDefinition()
{
}

FeatureDefinition::!FeatureDefinition()
{
	if (this->_featureDefinition != NULL)
	{
		OGRFeatureDefn::DestroyFeatureDefn(this->_featureDefinition);
		this->_featureDefinition = NULL;
	}
}

FieldDefinitionCollection^ FeatureDefinition::Fields::get()
{
	if (this->_fields == nullptr)
	{
		this->_fields = gcnew FieldDefinitionCollection(this->_featureDefinition);
	}

	return this->_fields;
}
