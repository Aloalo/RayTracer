#pragma once

#include "IntersectableObject.h"
#include "Ray.h"

class VolumetricObject :
	public IntersectableObject
{
public:
	VolumetricObject(const Material *mat);
	virtual ~VolumetricObject(void);
};

