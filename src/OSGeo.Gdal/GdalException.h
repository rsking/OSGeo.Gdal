#pragma once

namespace OSGeo
{
	/// <summary>Represents a GDAL exception.</summary>
	public ref class GdalException : public System::Exception
	{
	private:
		/// <summary>Initialises a new instance of the <see cref="GdalException"/> class.</summary>
		GdalException(System::String^ message);
	internal:
		/// <summary>Creates a new instance of the <see cref="GdalException"/> class.</summary>
		static GdalException^ Create();
	};
}

