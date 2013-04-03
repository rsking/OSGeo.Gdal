#pragma once

#include <ogr_feature.h>

namespace OSGeo
{
	namespace Ogr
	{
		ref class Geometry;

		public ref class Feature
		{
		private:
			Geometry^ _geometry;
			OGRFeature* _feature;
			~Feature();
			!Feature();
		internal:
			Feature(OGRFeature* feature);
		public:
			property Geometry^ Geometry
			{
				OSGeo::Ogr::Geometry^ get();
			}

			//System::Object GetValue(int i);

			/// <summary>Gets the string value of the specified field.</summary>
			/// <param name="i">The index of the field to find.</param>
			/// <returns>The string value of the specified field.</returns>
			/// <exception cref="System::IndexOutOfRangeException">The index passed was outside the range of 0 through FieldCount.</exception>
			System::String^ GetString(int i);
		};
	}
}