#include "StdAfx.h"
#include "VolumetricObject.h"


VolumetricObject::VolumetricObject(const Vector &color, float transparency, float indexOfRefraction, float reflectivity)
	: IntersectableObject(color, transparency, indexOfRefraction, reflectivity)
{
}

VolumetricObject::~VolumetricObject(void)
{
}