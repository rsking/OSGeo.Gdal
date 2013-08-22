#include "StdAfx.h"
#include "FeatureCollection.h"
#include "Feature.h"

using namespace System;
using namespace OSGeo::Ogr;

FeatureCollection::FeatureCollection(OGRLayer* layer)
{
	this->_layer = layer;
}

int FeatureCollection::Count::get()
{
	return this->_layer->GetFeatureCount();
}

Feature^ FeatureCollection::default::get(long fid)
{
	OGRFeature* feature = this->_layer->GetFeature(fid);
	return feature == NULL ? nullptr : gcnew Feature(feature);
}

void FeatureCollection::default::set(long fid, Feature^ feature)
{
	if (fid != feature->Handle->GetFID())
	{
		feature->Handle->SetFID(fid);
	}

	this->_layer->SetFeature(feature->Handle);
}

Generic::IEnumerator<Feature^>^ FeatureCollection::GetEnumerator()
{
	return gcnew Enumerator(this->_layer);
}

IEnumerator^ FeatureCollection::GetEnumeratorBase()
{
	return gcnew Enumerator(this->_layer);
}

FeatureCollection::Enumerator::Enumerator(OGRLayer* layer)
{
	this->_layer = layer;
}

Feature^ FeatureCollection::Enumerator::Current::get()
{
	return this->_currentFeature;
}

Object^ FeatureCollection::Enumerator::CurrentBase::get()
{
	return this->Current;
}

bool FeatureCollection::Enumerator::MoveNext()
{
	this->ReleaseCurrentFeature();
	OGRFeature* feature = this->_layer->GetNextFeature();
	if (feature != NULL)
	{
		this->_currentFeature = gcnew Feature(feature);
		return true;
	}

	return false;
}

void FeatureCollection::Enumerator::Reset()
{
	this->ReleaseCurrentFeature();
	this->_layer->ResetReading();
}

FeatureCollection::Enumerator::~Enumerator()
{
	// make sure we clear the current feature
	this->ReleaseCurrentFeature();
}

void FeatureCollection::Enumerator::ReleaseCurrentFeature()
{
	if (this->_currentFeature != nullptr)
	{
		this->_currentFeature->~Feature();
		this->_currentFeature = nullptr;
	}
}