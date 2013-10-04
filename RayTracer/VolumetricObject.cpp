#include "StdAfx.h"
#include "VolumetricObject.h"


VolumetricObject::VolumetricObject(const Material *mat)
	: IntersectableObject(mat)
{
}

VolumetricObject::~VolumetricObject(void)
{
}