#include "StdAfx.h"
#include <msclr/marshal.h>
#include "StringMarshaller.h"

using namespace System;
using namespace System::Text;
using namespace OSGeo;

StringMarshaller::StringMarshaller(void)
{
}

String^ StringMarshaller::GetStringAsUtf8(const char *value)
{
	msclr::interop::marshal_context cxt;
	array<unsigned char>^ bytes = System::Text::Encoding::Default->GetBytes(cxt.marshal_as<System::String^>(value));
	return System::Text::Encoding::UTF8->GetString(bytes);
}