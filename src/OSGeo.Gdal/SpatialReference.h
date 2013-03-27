#pragma once

#include <ogr_spatialref.h>
#include "SpatialReferenceImportFormat.h"
#include "SpatialReferenceExportFormat.h"

namespace OSGeo
{
	namespace Ogr
	{
		public ref class SpatialReference
		{
		private:
			OGRSpatialReference* _srs;
		internal:
			SpatialReference(OGRSpatialReference* srs);
			property OGRSpatialReference* Handle
			{
				OGRSpatialReference* get();
			}
		public:
			SpatialReference(System::String^ srs);
			~SpatialReference();

			static SpatialReference^ FromText(System::String^ text, SpatialReferenceImportFormat format);

			int Reference();
			int Dereference();
			property int ReferenceCount
			{
				int get();
			}

			void Release();

			SpatialReference^ Clone();

			SpatialReference^ CloneGeographic();

			virtual System::String^ ToString() override;

			System::String^ ToString(SpatialReferenceExportFormat format);
		};
	}
}
