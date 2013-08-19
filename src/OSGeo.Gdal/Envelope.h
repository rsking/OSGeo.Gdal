#pragma once

#include "ogr_core.h"

namespace OSGeo
{
	namespace Ogr
	{
		/// <summary>Represents a simple container for a bounding region.</summary>
		public ref class Envelope
		{
		private:
			/// <summary>The envelope.</summary>
			OGREnvelope* _envelope;
		internal:
			/// <summary>Initialises a new instance of the <see cref="Envelope"/> class.</summary>
			Envelope(OGREnvelope* _envelope);
		public:
			/// <summary>Initialises a new instance of the <see cref="Envelope"/> class.</summary>
			Envelope(void);
			
			/// <summary>Initialises a new instance of the <see cref="Envelope"/> class.</summary>
			Envelope(Envelope^ other);

			/// <summary>Gets or sets the minimum x-value.</summary>
			property double MinX { double get(); void set(double value); } 

			/// <summary>Gets or sets the maximum x-value.</summary>
			property double MaxX { double get(); void set(double value); } 

			/// <summary>Gets or sets the minimum y-value.</summary>
			property double MinY { double get(); void set(double value); } 

			/// <summary>Gets or sets the maximum y-value.</summary>
			property double MaxY { double get(); void set(double value); } 

			/// <summary>Gets a value indicating whether this instance is empty.</summary>
			property bool IsEmpty { bool get(); }

			/// <summary>Merges this instance with the specified instance.</summary>
			void Merge(Envelope^ other);

			/// <summary>Intersects this instance with the specified instance.</summary>
			void Intersect(Envelope^ other);

			/// <summary>Gets a value indicating whether this instance intersects with the specified instance.</summary>
			bool Intersects(Envelope^ other);
			
			/// <summary>Gets a value indicating whether this instance contains the specified instance.</summary>
			bool Contains(Envelope^ other);
		};
	}
}

