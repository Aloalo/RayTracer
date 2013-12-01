#pragma once

#include "Ray.h"
#include "Material.h"

class IntersectableObject
{
public:
	IntersectableObject(const Material *mat);
	virtual ~IntersectableObject(void);

	virtual bool intersect(const Ray &r, float &distance) const = 0;
	virtual void getNormalAtPoint(const Vector &point, Vector &normal) const = 0;

	const Material *mat;
};

