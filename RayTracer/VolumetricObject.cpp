#include "StdAfx.h"
#include "VolumetricObject.h"


VolumetricObject::VolumetricObject(const Vector &color, bool transparency, float indexOfRefraction, bool reflectivity)
	: IntersectableObject(color, transparency, indexOfRefraction, reflectivity)
{
}

VolumetricObject::~VolumetricObject(void)
{
}