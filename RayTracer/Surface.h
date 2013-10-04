#pragma once
#include "intersectableobject.h"
class Surface :
	public IntersectableObject
{
public:
	Surface(const Material *mat);
	virtual ~Surface(void);
};

