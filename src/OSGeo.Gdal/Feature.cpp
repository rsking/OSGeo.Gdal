#include "Stdafx.h"
#include <msclr/marshal.h>
#include "Feature.h"
#include "Geometry.h"
#include "StringMarshaller.h"

//using namespace OSGeo;
using namespace System;
using namespace OSGeo::Ogr;
using namespace System::Collections::Generic;

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

int Feature::FieldCount::get()
{
	return this->_feature->GetFieldCount();
}

Object^ Feature::Item::get(int i)
{
	return this->GetValue(i);
}

void Feature::Item::set(int index, Object^ value)
{
	Type^ type = value->GetType();
	if (type == int::typeid)
	{
		this->_feature->SetField(index, safe_cast<int>(value));
		return;
	}
	else if (type == double::typeid)
	{
		this->_feature->SetField(index, safe_cast<double>(value));
		return;
	}
	else if (type == DateTime::typeid)
	{
		DateTime^ temp = safe_cast<DateTime^>(value);
		this->_feature->SetField(index, temp->Year, temp->Month, temp->Day, temp->Hour, temp->Minute, temp->Second, temp->Kind == System::DateTimeKind::Local ? 1 : temp->Kind == System::DateTimeKind::Utc ? 2 : 0);
	}

	ICollection<int>^ collectionInt = dynamic_cast<ICollection<int>^>(value);
	if (collectionInt != nullptr)
	{
		int arrayLength = collectionInt->Count;
		array<int>^ tempArray = gcnew array<int>(arrayLength);
		collectionInt->CopyTo(tempArray, 0);
		pin_ptr<int> p1 = &tempArray[0];
		this->_feature->SetField(index, arrayLength, p1);
		p1 = nullptr;
		return;
	}

	ICollection<double>^ collectionDouble = dynamic_cast<ICollection<double>^>(value);
	if (collectionDouble != nullptr)
	{
		int arrayLength = collectionDouble->Count;
		array<double>^ tempArray = gcnew array<double>(arrayLength);
		collectionDouble->CopyTo(tempArray, 0);
		pin_ptr<double> p1 = &tempArray[0];
		this->_feature->SetField(index, arrayLength, p1);
		p1 = nullptr;
		return;
	}

	ICollection<String^>^ collectionString = dynamic_cast<ICollection<String^>^>(value);
	if (collectionString != nullptr)
	{
		int arrayLength = collectionString->Count;
		array<String^>^ tempArray = gcnew array<String^>(arrayLength);
		collectionString->CopyTo(tempArray, 0);
		char** stringArray = new char*[arrayLength];
		for (int i = 0; i < arrayLength; i++)
		{
			const char* charValue = StringMarshaller::FromUnicodeString(tempArray[i]);
			stringArray[i] = const_cast<char*>(charValue);
		}

		this->_feature->SetField(index, stringArray);
		return;
	}

	array<byte>^ byteArray = dynamic_cast<array<byte>^>(value);
	if (byteArray != nullptr)
	{
		pin_ptr<GByte> p1 = &byteArray[0];
		this->_feature->SetField(index, byteArray->Length, p1);
		p1 = nullptr;
		return;
	}

	String^ stringValue = dynamic_cast<String^>(value);
	if (stringValue == nullptr)
	{
		stringValue = value->ToString();
	}

	this->_feature->SetField(index, StringMarshaller::FromUnicodeString(stringValue));
}

Object^ Feature::Item::get(String^ name)
{
	return this->GetValue(this->GetOrdinal(name));
}

void Feature::Item::set(String^ name, Object^ value)
{
	this->Item[this->GetOrdinal(name)] = value;
}

bool Feature::GetBoolean(int i) {
	return this->_feature->GetFieldAsInteger(i) != 0;
}

unsigned char Feature::GetByte(int i) {
	return 0;
}

long long Feature::GetBytes(int i, long long fieldOffset, array<unsigned char>^ buffer, int bufferoffset, int length) {
	int bytesRead;
	GByte *bytes = this->_feature->GetFieldAsBinary(i, &bytesRead);

	if (buffer != nullptr) {
		for (int i = 0; i < length; i++) {
			buffer[bufferoffset] = bytes[fieldOffset];
		}
	}

	return bytesRead;
}

wchar_t Feature::GetChar(int i) {
	return 0;
}

long long Feature::GetChars(int i, long long fieldoffset, array<wchar_t>^ buffer, int bufferoffset, int length)
{
	return 0;
}

IDataReader^ Feature::GetData(int i)
{
	return safe_cast<IDataReader^>(this);
}

String^ Feature::GetDataTypeName(int i)
{
	const char* fieldTypeName = OGRFieldDefn::GetFieldTypeName(this->_feature->GetFieldDefnRef(i)->GetType());
	return StringMarshaller::GetStringAsUtf8(fieldTypeName);
}

DateTime Feature::GetDateTime(int i)
{
	int year, month, day, hour, minute, second, flag;
	if (this->_feature->GetFieldAsDateTime(i, &year, &month, &day, &hour, &minute, &second, &flag) == TRUE)
	{
		System::DateTimeKind kind;
		switch (flag)
		{
		case 0:
			kind = System::DateTimeKind::Unspecified;
		case 1:
			kind = System::DateTimeKind::Local;
		case 2:
			kind = System::DateTimeKind::Utc;
		}

		return *gcnew DateTime(year, month, day, hour, minute, second, kind);
	}
	
	return DateTime::MinValue;
}

Decimal Feature::GetDecimal(int i)
{
	throw gcnew System::InvalidCastException("Cannot cast to decimal");
}

double Feature::GetDouble(int i)
{
	return this->_feature->GetFieldAsDouble(i);
}

Type^ Feature::GetFieldType(int i)
{
	OGRFieldType fieldType = this->_feature->GetFieldDefnRef(i)->GetType();

	switch (fieldType)
	{
	case OFTInteger:
		return int::typeid;
	case OFTIntegerList:
		return array<int>::typeid;
	case OFTReal:
		return double::typeid;
	case OFTRealList:
		return array<double>::typeid;
	case OFTString: 
		return String::typeid;
	case OFTStringList:
		return array<String^>::typeid;
	case OFTWideString:
		return String::typeid;
	case OFTWideStringList:
		return array<String^>::typeid;
	case OFTBinary:
		return array<unsigned char>::typeid;
	case OFTDate:
	case OFTTime:
	case OFTDateTime:
		return DateTime::typeid;
	}

	return nullptr;
}

float Feature::GetFloat(int i)
{
	return 0;
}

Guid Feature::GetGuid(int i)
{
	return *gcnew Guid();
}

short Feature::GetInt16(int i)
{
	return 0;
}

int Feature::GetInt32(int i)
{
	return this->_feature->GetFieldAsInteger(i);
}

long long Feature::GetInt64(int i)
{
	return 0;
}

String^ Feature::GetName(int i)
{
	const char* fieldName = this->_feature->GetFieldDefnRef(i)->GetNameRef();
	return StringMarshaller::GetStringAsUtf8(fieldName);
}

int Feature::GetOrdinal(System::String^ name)
{
	const char* fieldName = StringMarshaller::FromUnicodeString(name);
	return this->_feature->GetFieldIndex(fieldName);
}

System::String^ Feature::GetString(int i)
{
	return StringMarshaller::GetStringAsUtf8(this->_feature->GetFieldAsString(i));
}

Object^ Feature::GetValue(int i)
{
	OGRFieldType fieldType = this->_feature->GetFieldDefnRef(i)->GetType();

	switch (fieldType)
	{
	case OFTInteger:
		return this->GetInt32(i);
	case OFTIntegerList:
		{
			int arrayLength;
			const int *integerArray = this->_feature->GetFieldAsIntegerList(i, &arrayLength);
			array<int>^ returnArray = gcnew array<int>(arrayLength);
			for (int i = 0; i < arrayLength; i++)
			{
				returnArray[i] = integerArray[i];
			}

			return returnArray;
		}
	case OFTReal:
		return this->GetDouble(i);
	case OFTRealList:
		{
			int arrayLength;
			const double *doubleArray = this->_feature->GetFieldAsDoubleList(i, &arrayLength);
			array<double>^ returnArray = gcnew array<double>(arrayLength);
			for (int i = 0; i < arrayLength; i++)
			{
				returnArray[i] = doubleArray[i];
			}

			return returnArray;
		}
	case OFTString: 
	case OFTWideString:
		return this->GetString(i);
	case OFTStringList:
	case OFTWideStringList:
		{
			char **stringArray = this->_feature->GetFieldAsStringList(i);
			int arrayLength = CSLCount(stringArray);
			array<String^>^ returnArray = gcnew array<String^>(arrayLength);
			for (int i = 0; i < arrayLength; i++)
			{
				returnArray[i] = StringMarshaller::GetStringAsUtf8(stringArray[i]);
			}

			return returnArray;
		}
	case OFTBinary:
		return this->GetBytes(i);
	case OFTDate:
	case OFTTime:
	case OFTDateTime:
		return this->GetDateTime(i);
	}

	return nullptr;
}

int Feature::GetValues(array<Object^>^ values)
{
	int length = values->Length < this->FieldCount ? values->Length : this->FieldCount;
	for (int i = 0; i < length; i++)
	{
		values[i] = this->GetValue(i);
	}

	return length;
}

bool Feature::IsDBNull(int i)
{
	return false;
}

array<unsigned char>^ Feature::GetBytes(int i)
{
	int byteCount;
	GByte *bytes = this->_feature->GetFieldAsBinary(i, &byteCount);
	array<unsigned char>^ returnArray = gcnew array<unsigned char>(byteCount);
	for (int i = 0; i < byteCount; i++)
	{
		returnArray[i] = bytes[i];
	}

	return returnArray;
}