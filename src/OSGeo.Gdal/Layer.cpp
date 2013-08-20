#include "Stdafx.h"
#include <msclr/marshal.h>
#include "Layer.h"
#include "FeatureDefinition.h"
#include "FeatureCollection.h"
#include "GdalException.h"
#include "Envelope.h"
#include "Geometry.h"

using namespace System;
using namespace OSGeo::Ogr;

Layer::Layer(OGRLayer* layer)
{
	this->_layer = layer;

	this->_capabilities = LayerCapabilities::None;
	if (this->_layer->TestCapability(OLCRandomRead))
	{
		this->_capabilities = this->_capabilities | LayerCapabilities::RandomRead;
	}

	if (this->_layer->TestCapability(OLCSequentialWrite))
	{
		this->_capabilities = this->_capabilities | LayerCapabilities::SequentialWrite;
	}

	if (this->_layer->TestCapability(OLCRandomWrite))
	{
		this->_capabilities = this->_capabilities | LayerCapabilities::RandomWrite;
	}
	
	if (this->_layer->TestCapability(OLCFastSpatialFilter))
	{
		this->_capabilities = this->_capabilities | LayerCapabilities::FastSpatialFilter;
	}
	
	if (this->_layer->TestCapability(OLCFastFeatureCount))
	{
		this->_capabilities = this->_capabilities | LayerCapabilities::FastFeatureCount;
	}
	
	if (this->_layer->TestCapability(OLCFastGetExtent))
	{
		this->_capabilities = this->_capabilities | LayerCapabilities::FastGetExtent;
	}
	
	if (this->_layer->TestCapability(OLCCreateField))
	{
		this->_capabilities = this->_capabilities | LayerCapabilities::CreateField;
	}
	
	if (this->_layer->TestCapability(OLCDeleteField))
	{
		this->_capabilities = this->_capabilities | LayerCapabilities::DeleteField;
	}
	
	if (this->_layer->TestCapability(OLCReorderFields))
	{
		this->_capabilities = this->_capabilities | LayerCapabilities::ReorderFields;
	}
	
	if (this->_layer->TestCapability(OLCAlterFieldDefn))
	{
		this->_capabilities = this->_capabilities | LayerCapabilities::AlterFieldDefn;
	}
	
	if (this->_layer->TestCapability(OLCTransactions))
	{
		this->_capabilities = this->_capabilities | LayerCapabilities::Transactions;
	}
	
	if (this->_layer->TestCapability(OLCDeleteFeature))
	{
		this->_capabilities = this->_capabilities | LayerCapabilities::DeleteFeature;
	}
	
	if (this->_layer->TestCapability(OLCFastSetNextByIndex))
	{
		this->_capabilities = this->_capabilities | LayerCapabilities::FastSetNextByIndex;
	}
	
	if (this->_layer->TestCapability(OLCStringsAsUTF8))
	{
		this->_capabilities = this->_capabilities | LayerCapabilities::StringsAsUTF8;
	}

	if (this->_layer->TestCapability(OLCIgnoreFields))
	{
		this->_capabilities = this->_capabilities | LayerCapabilities::IgnoreFields;
	}
}

Layer::~Layer()
{
	if (this->_definition != nullptr)
	{
		this->_definition->~FeatureDefinition();
		this->_definition = nullptr;
	}

	if (this->Features != nullptr)
	{
		this->_features = nullptr;
	}
}

Layer::!Layer()
{
}

void Layer::Reset()
{
	this->_layer->ResetReading();
}

String^ Layer::Name::get()
{
	msclr::interop::marshal_context cxt;
	return cxt.marshal_as<String^>(this->_layer->GetName());
}

FeatureDefinition^ Layer::Definition::get()
{
	if (_definition == nullptr)
	{
		_definition = gcnew FeatureDefinition(this->_layer->GetLayerDefn());
	}

	return _definition;
}

FeatureCollection^ Layer::Features::get()
{
	if (_features == nullptr)
	{
		_features= gcnew FeatureCollection(this->_layer);
	}

	return _features;
}

LayerCapabilities Layer::Capabilities::get()
{
	return this->_capabilities;
}

System::String^ Layer::ToString()
{
	return this->Name;
}

Envelope^ Layer::Extents::get()
{
	OGREnvelope* envelope = new OGREnvelope();
	OGRErr error = this->_layer->GetExtent(envelope);
	if (error != OGRERR_NONE)
	{
		throw OSGeo::GdalException::Create(error);
	}

	return gcnew Envelope(envelope);
}

Geometry^ Layer::SpatialFilter::get()
{
	return this->_spatialFilter == nullptr ? this->_spatialFilter = Geometry::FromGeometry(this->_layer->GetSpatialFilter()) : this->_spatialFilter;
}

void Layer::SpatialFilter::set(Geometry^ filter)
{
	this->_layer->SetSpatialFilter(filter->Handle);
}