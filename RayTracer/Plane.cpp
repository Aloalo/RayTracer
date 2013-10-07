#include "StdAfx.h"
#include "Plane.h"
#include "Essential.h"

Plane::Plane(const Material *mat, const Vector &n, const Vector &p)
	: Surface(mat), n(n.normalized()), p(p)
{

}

Plane::Plane(const Material *mat, const Vector &t0, const Vector &t1, const Vector &t2)
	: Surface(mat)
{
	n = crossProduct(t0 - t1, t1 - t2).normalized();
	p = t2;
}


Plane::~Plane(void)
{
}

bool Plane::intersect(const Ray &r, float *distance) const
{
	float t0 = dotProduct(n, p - r.origin);
	float t1 = dotProduct(r.direction, n);

	if(efl::abs(t0) <= efl::ZERO && efl::abs(t1) <= efl::ZERO)
	{
		*distance = 0.0f;
		return true;
	}
	else if(efl::abs(t1) <= efl::ZERO || (t0 / t1) < 0)
		return false;
	else
	{
		*distance = t0 / t1;
		return true;
	}
}

void Plane::getNormalAtPoint(const Vector &point, Vector &normal) const
{
	normal = n;
}
