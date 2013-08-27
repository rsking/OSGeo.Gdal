#include "Stdafx.h"
#include "CoordinateTransformation.h"
#include "SpatialReference.h"
#include "Point.h"

using namespace OSGeo::Ogr;

CoordinateTransformation::CoordinateTransformation(SpatialReference^ source, SpatialReference^ target)
{
	this->_coordinateTransformation =  OGRCreateCoordinateTransformation(source->Handle, target->Handle);
	this->_source = source;
	this->_target = target;
}

Point^ CoordinateTransformation::Transform(Point^ point)
{
	double x[] = { point->X };
	double y[] = { point->Y };
	double z[] = { point->Z };

	this->_coordinateTransformation->Transform(1, x, y, z);

	return gcnew Point(x[0], y[0], z[0]);
}

void CoordinateTransformation::Transform(System::Collections::Generic::IList<Point^>^ points)
{
	int count = points->Count;
	double* x = new double[count];
	double* y = new double[count];
	double* z = new double[count];

	for (int i = 0; i < count; i++)
	{
		x[i] = points[i]->X;
		y[i] = points[i]->Y;
		z[i] = points[i]->Z;
	}

	this->_coordinateTransformation->Transform(count, x, y, z);

	for (int i = 0; i < count; i++)
	{
		points[i]->X = x[i];
		points[i]->Y = y[i];
		points[i]->Z = z[i];
	}
}

void CoordinateTransformation::Transform(array<double>^ point)
{
	double x[] = { point[0] };
	double y[] = { point[1] };
	double z[] = { point->Length > 2 ? point[2] : 0 };

	this->_coordinateTransformation->Transform(1, x, y, point->Length > 2 ? z : NULL);

	point[0] = x[0];
	point[1] = y[0];
	if (point->Length > 2)
	{
		point[2] = z[0];
	}
}

SpatialReference^ CoordinateTransformation::Source::get()
{
	return this->_source;
}

SpatialReference^ CoordinateTransformation::Target::get()
{
	return this->_target;
}