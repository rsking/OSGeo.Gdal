#include "stdafx.h"
#include <msclr/marshal.h>
#include "FieldDefinition.h"

using namespace System;
using namespace OSGeo::Ogr;

FieldDefinition::FieldDefinition(OGRFieldDefn* fieldDefinition)
{
	this->_fieldDefinition = fieldDefinition;
}

String^ FieldDefinition::GetName(FieldType fieldType)
{
	msclr::interop::marshal_context ctx;
	return ctx.marshal_as<String^>(OGRFieldDefn::GetFieldTypeName((OGRFieldType)fieldType));
}

String^ FieldDefinition::Name::get()
{
	msclr::interop::marshal_context ctx;
	return ctx.marshal_as<String^>(this->_fieldDefinition->GetNameRef());
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


