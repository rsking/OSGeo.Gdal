#include <ogrsf_frmts.h>

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

			void Reset();
		};
	}
}