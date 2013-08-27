#include "StdAfx.h"
#include "IntersectableObject.h"


IntersectableObject::IntersectableObject(const Vector &color, float transparency, float reflectivity)
	: color(color), transparency(transparency), reflectivity(reflectivity)
{
}


IntersectableObject::~IntersectableObject(void)
{
}
