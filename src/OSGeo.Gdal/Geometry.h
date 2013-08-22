#pragma once

#include <ogr_geometry.h>
#include "GeometryTextFormat.h"

namespace OSGeo
{
	namespace Ogr
	{
		ref class SpatialReference;

		/// <summary>Abstract base class for all geometry classes.</summary>
		/// <remarks>Some spatial analysis methods require that OGR is built on the GEOS library to work properly. The precise meaning of methods that describe spatial relationships between geometries is described in the SFCOM, or other simple features interface specifications, like "OpenGIS® Implementation Specification for Geographic information - Simple feature access - Part 1: Common architecture".</remarks>
		public ref class Geometry abstract : System::IEquatable<Geometry^>
		{
		private:
			/// <summary>The OGR geometry.</summary>
			OGRGeometry* _geometry;
			
			/// <summary>The spatial reference system.</summary>
			SpatialReference^ _srs;
		protected:			
			/// <summary>Initialises a new instance of the <see	cref="Geometry"/> class.</summary>
			/// <param name="_geometry">The OGR geometry.</param>
			Geometry(OGRGeometry* _geometry);
		internal:
			/// <summary>Gets the handle.</summary>
			property OGRGeometry* Handle { OGRGeometry* get(); }
			
			/// <summary>Creates a <see cref="Geometry"/> from an OGR geometry.</summary>
			static Geometry^ FromGeometry(OGRGeometry* _geometry);
		public:
			/// <summary>Creates a <see cref="Geometry"/> from its WKB representation.</summary>
			/// <param name="wkb">The WKB representation.</param>
			static Geometry^ FromWkb(array<unsigned char>^ wkb);
			
			/// <summary>Creates a <see cref="Geometry"/> from its WKT representation.</summary>
			/// <param name="text">The WKT representation.</param>
			static Geometry^ FromText(System::String^ text);
			
			/// <summary>Creates a <see cref="Geometry"/> from its text representation.</summary>
			/// <param name="text">The text representation.</param>
			/// <param name="format">The format of <paramref name="text"/>.</param>
			static Geometry^ FromText(System::String^ text, GeometryTextFormat format);
			
			/// <summary>Make a copy of this object.</summary>
			virtual Geometry^ Clone();
			
			/// <summary>Clear geometry information. This restores the geometry to it's initial state after construction, and before assignment of actual geometry.</summary>
			void Empty();

			/// <summary>Force rings to be closed.</summary>
			void CloseRings();

			/// <summary>Modify the geometry such it has no segment longer then the given distance.</summary>
			/// <param name="maxLength">The maximum distance between 2 points after segmentization.</param>
			void Segmentize(double maxLength);
			
			/// <summary>Determines whether two geometries intersect. If GEOS is enabled, then this is done in rigorous fashion otherwise <see langword="true"/> is returned if the envelopes (bounding boxes) of the two features overlap.</summary>
			/// <param name="geometry">The geometry to test against.</param>
			/// <returns><see langword="true"/> if the geometries intersect; otherwise <see langword="false"/>.</returns>
			/// <remarks>The <paramref name="geometry"/> argument may be safely <see langword="null"/>, but in this case the method will always return <see langword="true"/>. That is, a <see langword="null"/> geometry is treated as being everywhere.</remarks>
			bool Intersects(Geometry^ geometry);
			
			/// <summary>Tests if this geometry and <paramref name="geometry"/> are disjoint.</summary>
			/// <param name="geometry">The geometry to test against.</param>
			/// <returns><see langword="true"/> if the geometries are disjoint; otherwise <see langword="false"/>.</returns>
			bool Disjoint(Geometry^ geometry);
			
			/// <summary>Tests if this geometry and the other passed into the method are touching.</summary>
			/// <param name="geometry">The geometry to test against.</param>
			/// <returns><see langword="true"/> if the geometries are touching; otherwise <see langword="false"/>.</returns>
			bool Touches(Geometry^ geometry);
			
			/// <summary>Tests if this geometry and the other passed into the method are crossing.</summary>
			/// <param name="geometry">The geometry to test against.</param>
			/// <returns><see langword="true"/> if the geometries are crossing; otherwise <see langword="false"/>.</returns>
			bool Crosses(Geometry^ geometry);
			
			/// <summary>Tests if actual geometry object is within the passed geometry.</summary>
			/// <param name="geometry">The geometry to test against.</param>
			/// <returns><see langword="true"/> if <paramref name="geometry"/> is within this geometry; otherwise <see langword="false"/>.</returns>
			bool Within(Geometry^ geometry);
			
			/// <summary>Tests if actual geometry object contains the passed geometry.</summary>
			/// <param name="geometry">The geometry to test against.</param>
			/// <returns><see langword="true"/> if geometry contains <paramref name="geometry"/>; otherwise <see langword="false"/>.</returns>
			bool Contains(Geometry^ geometry);
			
			/// <summary>Tests if this geometry and the other passed into the method overlap, that is their intersection has a non-zero area.</summary>
			/// <param name="geometry">The geometry to test against.</param>
			/// <returns><see langword="true"/> if the geometries are overlapping; otherwise <see langword="false"/>.</returns>
			bool Overlaps(Geometry^ geometry);

			/// <summary>Returns <see langword="true"/> if two geometries are equivalent; otherwise <see langword="false"/>.</summary>
			/// <param name="geometry">The geometry to test against.</param>
			/// <returns><see langword="true"/> if the geometries are equivalent; otherwise <see langword="false"/>.</returns>
			virtual bool Equals(Geometry^ geometry);

			/// <summary>Gets or sets the spatial reference.</summary>
			property SpatialReference^ SpatialReference
			{
				OSGeo::Ogr::SpatialReference^ get();
				void set(OSGeo::Ogr::SpatialReference^ value);
			}

			/// <summary>Gets the dimension of this object</summary>
			property int Dimensions
			{
				int get();
			}
			
			/// <summary>Gets or sets the coordinate dimensions.</summary>
			property int CoordinateDimensions
			{
				int get();
				void set(int value);
			}
			
			/// <summary>Gets a value indicating whether this instance has any points.</summary>
			property bool IsEmpty
			{
				bool get();
			}
			
			/// <summary>Gets a value indicating whether this instance is valid.</summary>
			property bool IsValid
			{
				bool get();
			}
			
			/// <summary>Gets a value indicating whether this instance is simple.</summary>
			property bool IsSimple
			{
				bool get();
			}
			
			/// <summary>Gets a value indicating whether this instance is a ring.</summary>
			property bool IsRing
			{
				bool get();
			}
			
			/// <summary>Convert this instance into well known text format.</summary>
			virtual System::String^ ToString() override;
			
			/// <summary>Convert this instance geometry into a text format.</summary>
			/// <param name="format">The format to convert to.</param>
			System::String^ ToString(GeometryTextFormat format);
			
			/// <summary>Converts this instance into well known binary format.</summary>
			array<unsigned char>^ ToBinary();
		};
	}
}