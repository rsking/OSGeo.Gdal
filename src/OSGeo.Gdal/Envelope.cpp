#include "Stdafx.h"
#include "Envelope.h"

using namespace OSGeo::Ogr;

Envelope::Envelope(OGREnvelope* envelope)
{
	this->_envelope = envelope;
}

Envelope::Envelope(void)
{
	this->_envelope = new OGREnvelope();
}

Envelope::Envelope(Envelope^ other)
{
	this->_envelope = new OGREnvelope(*other->_envelope);
}

double Envelope::MinX::get()
{
	return this->_envelope->MinX;
}

void Envelope::MinX::set(double value)
{
	this->_envelope->MinX = value;
}

double Envelope::MaxX::get()
{
	return this->_envelope->MaxX;
}

void Envelope::MaxX::set(double value)
{
	this->_envelope->MaxX = value;
}

double Envelope::MinY::get()
{
	return this->_envelope->MinY;
}

void Envelope::MinY::set(double value)
{
	this->_envelope->MinY = value;
}

double Envelope::MaxY::get()
{
	return this->_envelope->MaxY;
}

void Envelope::MaxY::set(double value)
{
	this->_envelope->MaxY = value;
}

bool Envelope::IsEmpty::get()
{
	return this->_envelope->IsInit() == FALSE;
}

void Envelope::Merge(Envelope^ other)
{
	this->_envelope->Merge(*other->_envelope);
}

void Envelope::Intersect(Envelope^ other)
{
	this->_envelope->Intersect(*other->_envelope);
}

bool Envelope::Intersects(Envelope^ other)
{
	return this->_envelope->Intersects(*other->_envelope) != 0;
}

bool Envelope::Contains(Envelope^ other)
{
	return this->_envelope->Contains(*other->_envelope) != 0;
}
