#pragma once

#include "VolumetricObject.h"

class Sphere :
	public VolumetricObject
{
public:
	Sphere(const Material *mat, const Vector &center, float radius);
	~Sphere(void);

	bool intersect(const Ray &r, float &distance) const;
	void getNormalAtPoint(const Vector &point, Vector &normal) const;

	Vector center;
	float radius, radius2;
};

