#pragma once

#include "IntersectableObject.h"
#include "Ray.h"

class VolumetricObject :
	public IntersectableObject
{
public:
	VolumetricObject(const Vector &color, bool transparency, float indexOfRefraction, bool reflectivity);
	virtual ~VolumetricObject(void);
};

