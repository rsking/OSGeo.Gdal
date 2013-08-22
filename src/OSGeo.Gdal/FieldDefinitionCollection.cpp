#include "Stdafx.h"
#include "FieldDefinitionCollection.h"
#include "FieldDefinition.h"
#include "StringMarshaller.h"

using namespace OSGeo::Ogr;

FieldDefinitionCollection::FieldDefinitionCollection(OGRFeatureDefn* featureDefinition)
{
	this->_featureDefinition = featureDefinition;
	this->_fieldDefinitions = gcnew System::Collections::Generic::Dictionary<int, FieldDefinition^>();
	OGRFieldDefn* temp = this->_featureDefinition->GetFieldDefn(0);
}

FieldDefinition^ FieldDefinitionCollection::default::get(int index)
{
	if (index < 0 || index >= this->Count)
	{
		throw gcnew System::IndexOutOfRangeException();
	}

	if (!this->_fieldDefinitions->ContainsKey(index))
	{
		this->_fieldDefinitions->Add(index, gcnew FieldDefinition(this->_featureDefinition->GetFieldDefn(index)));
	}

	return this->_fieldDefinitions[index];
}

void FieldDefinitionCollection::default::set(int index, FieldDefinition^ field)
{	
	throw gcnew NotSupportedException();
}

FieldDefinition^ FieldDefinitionCollection::default::get(String^ name)
{
	// get the index
	const char* fieldName = OSGeo::StringMarshaller::FromUnicodeString(name);
	int index = this->_featureDefinition->GetFieldIndex(fieldName);

	if (index == -1)
	{
		// field is not found
	}

	return this[index];
}

int FieldDefinitionCollection::Count::get()
{
	return this->_featureDefinition->GetFieldCount();
}

bool FieldDefinitionCollection::IsReadOnly::get()
{
	return false;
}

void FieldDefinitionCollection::Add(FieldDefinition^ field)
{
	this->_featureDefinition->AddFieldDefn(field->_fieldDefinition);
}

void FieldDefinitionCollection::Clear()
{
	while (this->_featureDefinition->GetFieldCount() > 0)
	{
		this->_featureDefinition->DeleteFieldDefn(0);
	}
}

bool FieldDefinitionCollection::Contains(FieldDefinition^ field)
{
	return this->IndexOf(field) != -1;
}

void FieldDefinitionCollection::CopyTo(array<FieldDefinition^>^ destination, int index)
{}

bool FieldDefinitionCollection::Remove(FieldDefinition^ field)
{
	int index = this->IndexOf(field);
	if (index >= 0)
	{
		return this->_featureDefinition->DeleteFieldDefn(index) != OGRERR_NONE;
	}

	return false;
}

void FieldDefinitionCollection::RemoveAt(int index)
{
	this->_featureDefinition->DeleteFieldDefn(index);
}

int FieldDefinitionCollection::IndexOf(FieldDefinition^ field)
{
	for (int i = 0; i < this->_featureDefinition->GetFieldCount(); i++)
	{
		if (this->_featureDefinition->GetFieldDefn(i) == field->_fieldDefinition)
		{
			return i;
		}
	}

	return -1;
}

void FieldDefinitionCollection::Insert(int index, FieldDefinition^ field)
{}

Generic::IEnumerator<FieldDefinition^>^ FieldDefinitionCollection::GetEnumerator()
{
	return gcnew Enumerator(this->_featureDefinition);
}

IEnumerator^ FieldDefinitionCollection::GetEnumeratorBase()
{
	return gcnew Enumerator(this->_featureDefinition);
}

FieldDefinitionCollection::Enumerator::Enumerator(OGRFeatureDefn* featureDefinition)
{
	this->_featureDefinition = featureDefinition;
	this->Reset();
}

FieldDefinition^ FieldDefinitionCollection::Enumerator::Current::get()
{
	return this->_currentFieldDefinition;
}

Object^ FieldDefinitionCollection::Enumerator::CurrentBase::get()
{
	return this->Current;
}

bool FieldDefinitionCollection::Enumerator::MoveNext()
{
	this->ReleaseCurrentFieldDefinition();

	this->_currentIndex++;
	if (this->_currentIndex < this->_featureDefinition->GetFieldCount())
	{
		this->_currentFieldDefinition = gcnew FieldDefinition(this->_featureDefinition->GetFieldDefn(this->_currentIndex));
		return true;
	}

	return false;
}

void FieldDefinitionCollection::Enumerator::Reset()
{
	this->ReleaseCurrentFieldDefinition();
	this->_currentIndex = -1;
}

FieldDefinitionCollection::Enumerator::~Enumerator()
{
	// make sure we clear the last current layer
	this->ReleaseCurrentFieldDefinition();
}

void FieldDefinitionCollection::Enumerator::ReleaseCurrentFieldDefinition()
{
	if (this->_currentFieldDefinition != nullptr)
	{
		this->_currentFieldDefinition->~FieldDefinition();
		this->_currentFieldDefinition = nullptr;
	}
}