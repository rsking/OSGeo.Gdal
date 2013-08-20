#include "StdAfx.h"
#include "GdalException.h"
#include "cpl_error.h"
#include "StringMarshaller.h"

using namespace OSGeo;

GdalException::GdalException(int error, System::String^ message) : Exception(message)
{
	this->HResult = error;
}

GdalException^ GdalException::Create(int error)
{
	const char* errorMessage = CPLGetLastErrorMsg();
	if (errorMessage == NULL)
	{
		return nullptr;
	}

	System::String^ errorString = StringMarshaller::GetStringAsUtf8(errorMessage);
	return gcnew GdalException(error, errorString);
}
