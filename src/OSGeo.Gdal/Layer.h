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

		public ref class Layer
		{
		private:
			FeatureCollection^ _features;
			FeatureDefinition^ _definition;
			LayerCapabilities _capabilities;
			OGRLayer* _layer;
			~Layer();
		protected:
			!Layer();
		internal:
			Layer(OGRLayer* layer);
		public:
			property String^ Name
			{
				String^ get();
			}

			property FeatureDefinition^ Definition
			{
				FeatureDefinition^ get();
			}

			property FeatureCollection^ Features
			{
				FeatureCollection^ get();
			}

			property LayerCapabilities Capabilities
			{
				LayerCapabilities get();
			}

			void Reset();
		};
	}
}