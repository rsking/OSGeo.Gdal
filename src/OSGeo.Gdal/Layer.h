#pragma once

#include <ogrsf_frmts.h>
#include "LayerCapabilities.h"

using namespace System;

namespace OSGeo 
{
	namespace Ogr
	{
		ref class FeatureCollection;
		ref class FeatureDefinition;
		ref class Envelope;
		ref class Geometry;
		
		/// <summary>Represents an OGR Layer.</summary>
		public ref class Layer sealed
		{
		private:
			/// <summary>The feature collection.</summary>
			FeatureCollection^ _features;

			/// <summary>The feature definition.</summary>
			FeatureDefinition^ _definition;
			
			/// <summary>The layer capabilities.</summary>
			LayerCapabilities _capabilities;
			
			/// <summary>The spatial filter.</summary>
			Geometry^ _spatialFilter;
			
			/// <summary>The OGR layer.</summary>
			OGRLayer* _layer;
			
			/// <summary>Disposes this instance.</summary>
			~Layer();

			/// <summary>Finalises this instance.</summary>
			!Layer();
		internal:
			/// <summary>Initialises a new instance of the <see cref="Layer"/> class.</summary>
			Layer(OGRLayer* layer);
		public:
			/// <summary>Gets the name of the layer.</summary>
			property String^ Name
			{
				String^ get();
			}
			
			/// <summary>Gets the feature definition.</summary>
			property FeatureDefinition^ Definition
			{
				FeatureDefinition^ get();
			}
			
			/// <summary>Gets the features.</summary>
			property FeatureCollection^ Features
			{
				FeatureCollection^ get();
			}
			
			/// <summary>Gets the capabilities.</summary>
			property LayerCapabilities Capabilities
			{
				LayerCapabilities get();
			}
			
			/// <summary>Gets the extents.</summary>
			property Envelope^ Extents
			{
				Envelope^ get();
			}
			
			/// <summary>Gets or sets the spatial filter.</summary>
			property Geometry^ SpatialFilter
			{
				Geometry^ get();
				void set(Geometry^ filter);
			}
						
			/// <summary>Converts this instance into a human-readable string value.</summary>
			virtual System::String^ ToString() override;
		};
	}
}