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
	return gcnew FeatureEnumerator(this->_layer);
}

IEnumerator^ FeatureCollection::GetEnumeratorBase()
{
	return gcnew FeatureEnumerator(this->_layer);
}

FeatureCollection::FeatureEnumerator::FeatureEnumerator(OGRLayer* layer)
{
	this->_layer = layer;
}

Feature^ FeatureCollection::FeatureEnumerator::Current::get()
{
	return this->_currentFeature;
}

Object^ FeatureCollection::FeatureEnumerator::CurrentBase::get()
{
	return this->Current;
}

bool FeatureCollection::FeatureEnumerator::MoveNext()
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

void FeatureCollection::FeatureEnumerator::Reset()
{
	this->ReleaseCurrentFeature();
	this->_layer->ResetReading();
}

FeatureCollection::FeatureEnumerator::~FeatureEnumerator()
{
	// make sure we clear the current feature
	this->ReleaseCurrentFeature();
}

void FeatureCollection::FeatureEnumerator::ReleaseCurrentFeature()
{
	if (this->_currentFeature != nullptr)
	{
		this->_currentFeature->~Feature();
		this->_currentFeature = nullptr;
	}
}