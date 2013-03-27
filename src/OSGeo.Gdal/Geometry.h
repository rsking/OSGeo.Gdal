#pragma once

#include <ogr_geometry.h>
#include "GeometryTextFormat.h"

namespace OSGeo
{
	namespace Ogr
	{
		ref class SpatialReference;

		public ref class Geometry abstract : System::IEquatable<Geometry^>
		{
		private:
			OGRGeometry* _geometry;
			SpatialReference^ _srs;
		protected:
			Geometry();
			Geometry(OGRGeometry* _geometry);
			virtual void SetGeometryObject(OGRGeometry* _geometry);
		internal:
			property OGRGeometry* Handle { OGRGeometry* get(); }
			static Geometry^ FromGeometry(OGRGeometry* _geometry);
		public:
			static Geometry^ FromWkb(array<unsigned char>^ wkb);

			static Geometry^ FromText(System::String^ text);

			static Geometry^ FromText(System::String^ text, GeometryTextFormat format);

			virtual Geometry^ Clone();

			/// <summary>Clear geometry information. This restores the geometry to it's initial state after construction, and before assignment of actual geometry.</summary>
			void Empty();

			/// <summary>Force rings to be closed.</summary>
			void CloseRings();

			void Segmentize(double maxLength);

			bool Intersects(Geometry^ geometry);

			bool Disjoint(Geometry^ geometry);

			bool Touches(Geometry^ geometry);

			bool Crosses(Geometry^ geometry);

			bool Within(Geometry^ geometry);

			bool Contains(Geometry^ geometry);

			bool Overlaps(Geometry^ geometry);

			/// <summary>Returns <see langword="true"/> if two geometries are equivalent; otherwise <see langword="false"/>.</summary>
			virtual bool Equals(Geometry^ geometry);

			property SpatialReference^ SpatialReference
			{
				OSGeo::Ogr::SpatialReference^ get();
				void set(OSGeo::Ogr::SpatialReference^ value);
			}

			property int Dimensions
			{
				int get();
			}

			property int CoordinateDimensions
			{
				int get();
				/// <summary>Set the coordinate dimension.</summary>
				void set(int value);
			}

			property bool IsEmpty
			{
				bool get();
			}

			property bool IsValid
			{
				bool get();
			}

			property bool IsSimple
			{
				bool get();
			}

			property bool IsRing
			{
				bool get();
			}

			virtual System::String^ ToString() override;

			System::String^ ToString(GeometryTextFormat format);

			array<unsigned char>^ ToBinary();
		};
	}
}