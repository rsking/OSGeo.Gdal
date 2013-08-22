#include "StdAfx.h"
#include "LayerCollection.h"
#include "Layer.h"

using namespace System;
using namespace System::Collections;
using namespace OSGeo::Ogr;

LayerCollection::LayerCollection(OGRDataSource* dataSource)
{
	this->_dataSource = dataSource;
}

int LayerCollection::Count::get()
{
	return this->_dataSource->GetLayerCount();
}

Generic::IEnumerator<Layer^>^ LayerCollection::GetEnumerator()
{
	return gcnew Enumerator(this->_dataSource);
}

IEnumerator^ LayerCollection::GetEnumeratorBase()
{
	return gcnew Enumerator(this->_dataSource);
}

LayerCollection::Enumerator::Enumerator(OGRDataSource* dataSource)
{
	this->_dataSource = dataSource;
	this->_currentIndex = -1;
}

Layer^ LayerCollection::Enumerator::Current::get()
{
	return this->_currentLayer;
}

Object^ LayerCollection::Enumerator::CurrentBase::get()
{
	return this->Current;
}

bool LayerCollection::Enumerator::MoveNext()
{
	this->ReleaseCurrentLayer();

	this->_currentIndex++;
	if (this->_currentIndex < this->_dataSource->GetLayerCount())
	{
		this->_currentLayer = gcnew Layer(this->_dataSource->GetLayer(this->_currentIndex));
		return true;
	}

	return false;
}

void LayerCollection::Enumerator::Reset()
{
	this->ReleaseCurrentLayer();
	this->_currentIndex = -1;
}

LayerCollection::Enumerator::~Enumerator()
{
	// make sure we clear the last current layer
	this->ReleaseCurrentLayer();
}

void LayerCollection::Enumerator::ReleaseCurrentLayer()
{
	if (this->_currentLayer != nullptr)
	{
		this->_currentLayer->~Layer();
		this->_currentLayer = nullptr;
	}
}
