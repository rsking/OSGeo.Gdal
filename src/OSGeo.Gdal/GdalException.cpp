#include "StdAfx.h"
#include "GdalException.h"
#include "cpl_error.h"
#include "StringMarshaller.h"

using namespace OSGeo;

GdalException::GdalException(System::String^ message) : Exception(message)
{
	//CPLGetLastErrorMsg
}

GdalException^ GdalException::Create()
{
	const char* errorMessage = CPLGetLastErrorMsg();
	if (errorMessage == NULL)
	{
		return nullptr;
	}

	System::String^ errorString = StringMarshaller::GetStringAsUtf8(errorMessage);
	return gcnew GdalException(errorString);
}
