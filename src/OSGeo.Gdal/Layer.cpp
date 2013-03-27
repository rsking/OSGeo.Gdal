#include "Stdafx.h"
#include <msclr/marshal.h>
#include "Layer.h"
#include "FeatureDefinition.h"
#include "FeatureCollection.h"

using namespace System;
using namespace OSGeo::Ogr;

Layer::Layer(OGRLayer* layer)
{
	this->_layer = layer;
}

Layer::~Layer()
{
	//this->!Layer();
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