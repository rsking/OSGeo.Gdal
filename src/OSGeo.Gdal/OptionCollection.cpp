#include "stdafx.h"
#include <msclr/marshal.h>
#include "cpl_conv.h"
#include "OptionCollection.h"

OSGeo::OptionCollection::OptionCollection(void)
{
}

System::String^ OSGeo::OptionCollection::default::get(System::String^ name)
{
	msclr::interop::marshal_context ctx;
	const char* nameValue = ctx.marshal_as<const char *>(name);
	const char* optionValue = CPLGetConfigOption(nameValue, NULL);

	return optionValue == NULL ? nullptr : ctx.marshal_as<System::String^>(optionValue);
}

void OSGeo::OptionCollection::default::set(System::String^ name, System::String^ value)
{
	msclr::interop::marshal_context ctx;
	const char* nameValue = ctx.marshal_as<const char *>(name);
	const char* optionValue = value == nullptr ? NULL : ctx.marshal_as<const char *>(value);

	CPLSetConfigOption(nameValue, optionValue);

}
