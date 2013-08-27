#include "StdAfx.h"
#include "VolumetricObject.h"


VolumetricObject::VolumetricObject(const Vector &color, float transparency, float reflectivity)
	: IntersectableObject(color, transparency, reflectivity)
{
}

VolumetricObject::~VolumetricObject(void)
{
}