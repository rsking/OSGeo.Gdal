#pragma once

namespace OSGeo
{
	public ref class OptionCollection
	{
	internal:
		OptionCollection(void);
	public:
		property System::String^ default[System::String^]
		{
			System::String^ get(System::String^ name);
			void set(System::String^ name, System::String^ value);
		}
	};
}

