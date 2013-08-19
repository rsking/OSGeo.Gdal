#pragma once

#include <ogr_spatialref.h>
#include "SpatialReferenceImportFormat.h"
#include "SpatialReferenceExportFormat.h"

namespace OSGeo
{
	namespace Ogr
	{
		/// <summary>Represents a spatial reference.</summary>
		public ref class SpatialReference sealed : public System::IEquatable<SpatialReference^>
		{
		private:
			/// <summary>The OGR spatial reference.</summary>
			OGRSpatialReference* _srs;
			
			/// <summary>Disposes this instance.</summary>
			~SpatialReference();
		internal:
			/// <summary>Initialises a new instance of the <see cref="SpatialReference" /> class.</summary>
			SpatialReference(OGRSpatialReference* srs);

			/// <summary>Gets the handle.</summary>
			property OGRSpatialReference* Handle
			{
				OGRSpatialReference* get();
			}

			/// <summary>Creates a new <see cref="SpatialReference"/> from the specified <see cref="OGRSpatialReference"/> object.</summary>
			static SpatialReference^ FromOGRSpatialReference(OGRSpatialReference* srs);
		public:
			/// <summary>Initialises a new instance of the <see cref="SpatialReference" /> class.</summary>
			/// <param name="srs">The WKT representation of the SRS.</param>
			SpatialReference(System::String^ srs);
			
			/// <summary>Creates a new <see cref="SpatialReference"/> from the specified string representation.</summary>
			/// <param name="text">The text representation of the SRS.</param>
			/// <param name="format">The format of <paramref name="text"/>.</param>
			static SpatialReference^ FromText(System::String^ text, SpatialReferenceImportFormat format);

			/// <summary>References this instance.</summary>
			int Reference();

			/// <summary>Dereferences this instance.</summary>
			int Dereference();

			/// <summary>Gets the current reference count.</summary>
			property int ReferenceCount
			{
				int get();
			}

			/// <summary>Releases this instance.</summary>
			void Release();

			/// <summary>Clones this instance.</summary>
			SpatialReference^ Clone();

			/// <summary>Clones the geographic portion of this instance.</summary>
			SpatialReference^ CloneGeographic();

			/// <summary>Converts this instance into its WKT format.</summary>
			virtual System::String^ ToString() override;

			/// <summary>Converts this instance into a human-readable representation.</summary>
			/// <param name="format">The export format.</param>
			System::String^ ToString(SpatialReferenceExportFormat format);

			/// <summary>Determines whether this instance is of the same type and equivalent to the specified <see cref="other"/>.</summary>
			virtual bool Equals(System::Object^ other) override;

			/// <summary>Determines whether this instance is equivalent to the specified <see cref="SpatialReference"/>.</summary>
			virtual bool Equals(SpatialReference^ other);
		};
	}
}
