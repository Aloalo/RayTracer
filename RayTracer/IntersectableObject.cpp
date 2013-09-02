#include "StdAfx.h"
#include "IntersectableObject.h"


IntersectableObject::IntersectableObject(const Vector &color, bool transparency, float indexOfRefraction, bool reflectivity)
	: color(color), transparency(transparency), ior(indexOfRefraction), reflectivity(reflectivity)
{
}


IntersectableObject::~IntersectableObject(void)
{
}
