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

void Envelope3D::Merge(Envelope3D^ other)
{
	this->_envelope->Merge(*other->_envelope);
}
			
void Envelope3D::Merge(double x, double y, double z)
{
	this->_envelope->Merge(x, y, z);
}

void Envelope3D::Intersect(Envelope3D^ other)
{
	this->_envelope->Intersect(*other->_envelope);
}

bool Envelope3D::Intersects(Envelope3D^ other)
{
	return this->_envelope->Intersects(*other->_envelope) != FALSE;
}
			
bool Envelope3D::Contains(Envelope3D^ other)
{
	return this->_envelope->Contains(*other->_envelope) != FALSE;
}
