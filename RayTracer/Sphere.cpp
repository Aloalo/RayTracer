#include "StdAfx.h"
#include "Sphere.h"
#include <cmath>

Sphere::Sphere(const Material *mat, const Vector &center, float radius)
	: VolumetricObject(mat), center(center), radius(radius), radius2(radius * radius)
{
}


Sphere::~Sphere(void)
{
}

bool Sphere::intersect(const Ray &r, float *distance) const
{
	Vector l = center - r.origin;

	float tca = dotProduct(l, r.direction);
	if (tca < 0)
		return false;

	float d2 = dotProduct(l, l) - tca * tca;
	if (d2 > radius2)
		return false;

	float thc = sqrt(radius2 - d2);
	*distance = (tca - thc) > 0.0f ? tca - thc : tca + thc;

	return true;
}

void Sphere::getNormalAtPoint(const Vector &point, Vector &normal) const
{
	normal = (point - center).normalized();
}
