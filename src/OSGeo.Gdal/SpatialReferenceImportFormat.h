#pragma once

namespace OSGeo
{
	namespace Ogr
	{
		public enum class SpatialReferenceImportFormat : int
		{
			Wkt,
			Proj4,
			Esri,
			Pci,
			WmsAuto,
			Xml,
			Urn,
			Url,
			MapInfo
		};
	}
}