#pragma once

namespace OSGeo
{
	namespace Ogr
	{
		/// <summary>The <see cref="SpatialReference"/> export format.</summary>
		public enum class SpatialReferenceExportFormat : int
		{
			/// <summary>Well-Known Text.</summary>
			Wkt,

			/// <summary>Pretty <see cref="Wkt"/>.</summary>
			PrettyWkt,

			/// <summary>Proj4 string.</summary>
			Proj4,

			/// <summary>XML string.</summary>
			Xml,

			/// <summary>MapInfo format.</summary>
			MapInfo
		};
	}
}