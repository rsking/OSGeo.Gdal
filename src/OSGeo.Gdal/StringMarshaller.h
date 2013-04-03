#pragma once

using namespace System;

namespace OSGeo
{
	ref class StringMarshaller
	{
	private:
		StringMarshaller(void);
	public:
		static String^ GetStringAsUtf8(const char *value);
	};
}

