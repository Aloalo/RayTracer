#pragma once

#include "Ray.h"

class IntersectableObject
{
public:
	IntersectableObject(const Vector &color, float transparency, float indexOfRefraction, float reflectivity);
	virtual ~IntersectableObject(void);

	virtual bool intersect(const Ray &r, float *distance) const = 0;
	virtual void getNormalAtPoint(const Vector &point, Vector &normal) const = 0;

	Vector color;
	float transparency, ior, reflectivity;
};

