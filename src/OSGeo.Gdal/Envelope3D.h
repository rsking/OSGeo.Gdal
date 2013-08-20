#pragma once

#include "ogr_core.h"
#include "Envelope.h"

namespace OSGeo
{
	namespace Ogr
	{
		public ref class Envelope3D sealed : public Envelope
		{
		private:
			OGREnvelope3D* _envelope;
		internal:
			Envelope3D(OGREnvelope3D* envelope);
		public:
			/// <summary>Initialises a new instance of the <see cref="Envelope3D"/> class.</summary>
			Envelope3D(void);
			
			/// <summary>Initialises a new instance of the <see cref="Envelope3D"/> class.</summary>
			Envelope3D(Envelope3D^ other);

			/// <summary>Gets or sets the minimum y-value.</summary>
			property double MinZ { double get(); void set(double value); }
			
			/// <summary>Gets or sets the maximum y-value.</summary>
			property double MaxZ { double get(); void set(double value); }
			
			/// <summary>Gets a value indicating whether this instance is empty.</summary>
			property bool IsEmpty { bool get(); }

			/// <summary>Merges this instance with the specified instance.</summary>
			void Merge(Envelope3D^ other);
			
			/// <summary>Merges this instance with the specified values.</summary>
			void Merge(double x, double y, double z);

			/// <summary>Intersects this instance with the specified instance.</summary>
			void Intersect(Envelope3D^ other);

			/// <summary>Gets a value indicating whether this instance intersects with the specified instance.</summary>
			bool Intersects(Envelope3D^ other);
			
			/// <summary>Gets a value indicating whether this instance contains the specified instance.</summary>
			bool Contains(Envelope3D^ other);
		};
	}
}
