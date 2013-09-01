#include "StdAfx.h"
#include "IntersectableObject.h"


IntersectableObject::IntersectableObject(const Vector &color, float transparency, float indexOfRefraction, float reflectivity)
	: color(color), transparency(transparency), ior(indexOfRefraction), reflectivity(reflectivity)
{
}


IntersectableObject::~IntersectableObject(void)
{
}
