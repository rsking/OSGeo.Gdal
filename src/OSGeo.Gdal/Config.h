#pragma once

#include "OptionCollection.h"

namespace OSGeo
{
	public ref class Config sealed
	{
	private:
		static OptionCollection^ _options = gcnew OptionCollection();

		Config(void);
	public:
		property static OptionCollection^ Options
		{
			OptionCollection^ get();
		}
	};
}

