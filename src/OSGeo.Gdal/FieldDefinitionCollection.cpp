#include "stdafx.h"
#include "FieldDefinitionCollection.h"
#include "FieldDefinition.h"

using namespace OSGeo::Ogr;

FieldDefinitionCollection::FieldDefinitionCollection(OGRFeatureDefn* featureDefinition)
{
	this->_featureDefinition = featureDefinition;
}

int FieldDefinitionCollection::Count::get()
{
	return this->_featureDefinition->GetFieldCount();
}

Generic::IEnumerator<FieldDefinition^>^ FieldDefinitionCollection::GetEnumerator()
{
	return gcnew FieldDefinitionEnumerator(this->_featureDefinition);
}

IEnumerator^ FieldDefinitionCollection::GetEnumeratorBase()
{
	return gcnew FieldDefinitionEnumerator(this->_featureDefinition);
}

FieldDefinitionEnumerator::FieldDefinitionEnumerator(OGRFeatureDefn* featureDefinition)
{
	this->_featureDefinition = featureDefinition;
	this->_currentIndex = -1;
}

FieldDefinition^ FieldDefinitionEnumerator::Current::get()
{
	return gcnew FieldDefinition(this->_currentFieldDefinition);
}

Object^ FieldDefinitionEnumerator::CurrentBase::get()
{
	return this->Current;
}

bool FieldDefinitionEnumerator::MoveNext()
{
	this->_currentIndex++;
	if (this->_currentIndex < this->_featureDefinition->GetFieldCount())
	{
		
		this->_currentFieldDefinition = this->_featureDefinition->GetFieldDefn(this->_currentIndex);
		return true;
	}

	return false;
}

void FieldDefinitionEnumerator::Reset()
{
	this->_currentIndex = -1;
}

FieldDefinitionEnumerator::~FieldDefinitionEnumerator()
{
	// make sure we clear the last current layer
	this->_currentFieldDefinition = NULL;
}
