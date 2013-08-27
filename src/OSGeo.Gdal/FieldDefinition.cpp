#include "Stdafx.h"
#include <msclr/marshal.h>
#include "FieldDefinition.h"

using namespace System;
using namespace OSGeo::Ogr;

FieldDefinition::FieldDefinition(OGRFieldDefn* fieldDefinition)
{
	this->_fieldDefinition = fieldDefinition;
}

FieldDefinition::FieldDefinition(String^ name, FieldType type)
{
	msclr::interop::marshal_context ctx;
	this->_fieldDefinition = new OGRFieldDefn(ctx.marshal_as<const char *>(name), (OGRFieldType)type);
}

String^ FieldDefinition::GetName(FieldType fieldType)
{
	return msclr::interop::marshal_as<String^>(OGRFieldDefn::GetFieldTypeName((OGRFieldType)fieldType));
}

String^ FieldDefinition::Name::get()
{
	return msclr::interop::marshal_as<String^>(this->_fieldDefinition->GetNameRef());
}

void FieldDefinition::Name::set(String^ value)
{
	msclr::interop::marshal_context ctx;
	this->_fieldDefinition->SetName(ctx.marshal_as<const char*>(value));
}

FieldType FieldDefinition::Type::get()
{
	return (FieldType)this->_fieldDefinition->GetType();
}

void FieldDefinition::Type::set(FieldType value)
{
	this->_fieldDefinition->SetType((OGRFieldType)value);
}

System::String^ FieldDefinition::ToString()
{
	return System::String::Format(System::Globalization::CultureInfo::CurrentCulture, "{0} - {1}", this->Name, FieldDefinition::GetName(this->Type));
}