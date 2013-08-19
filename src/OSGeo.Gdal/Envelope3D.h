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

			property bool IsEmpty { bool get(); }
		};
	}
}
