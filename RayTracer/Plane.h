#pragma once
#include "surface.h"
class Plane :
	public Surface
{
public:
	Plane(const Material *mat, const Vector &n, const Vector &p);
	Plane(const Material *mat, const Vector &t0, const Vector &t1, const Vector &t2);
	~Plane(void);

	bool intersect(const Ray &r, float *distance) const;
	void getNormalAtPoint(const Vector &point, Vector &normal) const;

	Vector n, p;
};

