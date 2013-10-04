#include "StdAfx.h"
#include "Surface.h"

Surface::Surface(const Material *mat)
	: IntersectableObject(mat)
{
}

Surface::~Surface(void)
{
}
