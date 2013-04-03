#pragma once

namespace OSGeo
{
	namespace Ogr
	{
		public enum class GeometryTextFormat : int
		{
			/// <summary>Well Known Text</summary>
			Wkt,
			/// <summary>Geography Markup Language.</summary>
			Gml,
			/// <summary>Keyhole Markup Language.</summary>
			Kml,
			/// <summary>JavaScript Object Notation.</summary>
			Json
		};
	}
}