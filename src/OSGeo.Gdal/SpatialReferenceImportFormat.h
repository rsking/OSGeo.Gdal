#pragma once

namespace OSGeo
{
	namespace Ogr
	{
		ref class SpatialReference;

		/// <summary>The <see cref="SpatialReference"/> import format.</summary>
		public enum class SpatialReferenceImportFormat : int
		{
			/// <summary>Well-Known Text.</summary>
			Wkt,

			/// <summary>Proj4 string.</summary>
			Proj4,

			/// <summary>ESRI string.</summary>
			Esri,

			/// <summary>PCI string.</summary>
			Pci,

			/// <summary>WMS auto string.</summary>
			WmsAuto,

			/// <summary>XML string.</summary>
			Xml,

			/// <summary>URN string.</summary>
			Urn,
			
			/// <summary>URL string.</summary>
			Url,

			/// <summary>MapInfo format.</summary>
			MapInfo
		};
	}
}