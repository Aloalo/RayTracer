#pragma once

#include "IntersectableObject.h"
#include "Ray.h"

class VolumetricObject :
	public IntersectableObject
{
public:
	VolumetricObject(const Vector &color, float transparency, float reflectivity);
	virtual ~VolumetricObject(void);
};

