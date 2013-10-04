#include "StdAfx.h"
#include "IntersectableObject.h"

IntersectableObject::IntersectableObject(const Material *mat)
	: mat(mat)
{
}


IntersectableObject::~IntersectableObject(void)
{
	delete mat;
}
