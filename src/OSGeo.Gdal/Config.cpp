#include "stdafx.h"
#include "Config.h"

OSGeo::Config::Config(void)
{
}

OSGeo::OptionCollection^ OSGeo::Config::Options::get()
{
	return _options;
}

/*
System::String^ OSGeo::Config::Options::get(System::String^ name)
{
	msclr::interop::marshal_context ctx;
	const char* nameValue = ctx.marshal_as<const char *>(name);
	const char* optionValue = CPLGetConfigOption(nameValue, NULL);

	return optionValue == NULL ? nullptr : ctx.marshal_as<System::String^>(optionValue);
}

void OSGeo::Config::Options::set(System::String^ name, System::String^ value)
{
	msclr::interop::marshal_context ctx;
	const char* nameValue = ctx.marshal_as<const char *>(name);
	const char* optionValue = value == nullptr ? NULL : ctx.marshal_as<const char *>(value);

	CPLSetConfigOption(nameValue, optionValue);

}*/
