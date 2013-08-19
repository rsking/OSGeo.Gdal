#include "stdafx.h"
#include "Envelope3D.h"

using namespace OSGeo::Ogr;

Envelope3D::Envelope3D(OGREnvelope3D* envelope) : Envelope(envelope)
{
	this->_envelope = envelope;
}

Envelope3D::Envelope3D(void) : Envelope(this->_envelope = new OGREnvelope3D())
{
}

Envelope3D::Envelope3D(Envelope3D^ other) : Envelope(this->_envelope = new OGREnvelope3D(*other->_envelope))
{
}

double Envelope3D::MinZ::get()
{
	return this->_envelope->MinZ;
}

void Envelope3D::MinZ::set(double value)
{
	this->_envelope->MinZ = value;
}

double Envelope3D::MaxZ::get()
{
	return this->_envelope->MaxZ;
}

void Envelope3D::MaxZ::set(double value)
{
	this->_envelope->MaxZ = value;
}

bool Envelope3D::IsEmpty::get()
{
	return this->_envelope->IsInit() == FALSE;
}
