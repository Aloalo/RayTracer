#include "StdAfx.h"
#include "Ray.h"

Ray::Ray(void)
{
}

Ray::Ray(const Vector &origin, const Vector &direction)
	: origin(origin), direction(direction)
{
}

Ray::~Ray(void)
{
}

//double Ray::hit(Surface *sf) const
//{
//	if(Plane *pp = dynamic_cast<Plane*>(sf))
//		return hit(*pp);
//	else if(Triangle *pp = dynamic_cast<Triangle*>(sf))
//		return hit(*pp);
//	else if(SquareAA *pp = dynamic_cast<SquareAA*>(sf))
//		return hit(*pp);
//	else
//		return INF;
//}
//
//double Ray::hit(const Plane &pi) const
//{
//	double t0 = dotProduct(pi.n, pi.p - a);
//	double t1 = dotProduct(b, pi.n);
//
//	if(abs(t0) <= EPS && abs(t1) <= EPS)
//		return 0;
//	else if(abs(t1) <= EPS || (t0 / t1) < 0)
//		return INF;
//	else
//		return t0 / t1;
//}
//
//double Ray::hit(const Triangle &t) const
//{
//	double d = hit(Plane(t));
//
//	if(d == INF)
//		return INF;
//	if(t.containsPointInPlane(Vector(a + d * b)))
//		return d;
//	return INF;
//}
//
//double Ray::hit(const SquareAA &sq) const
//{
//	double d = hit(Plane(sq));
//
//	if(d == INF)
//		return INF;
//	if(sq.containsPointInPlane(Vector(a + d * b)))
//		return d;
//	return INF;
//}
//
//double Ray::hit(const RectangleAA &sq) const
//{
//	double d = hit(Plane(sq));
//
//	if(d == INF)
//		return INF;
//	if(sq.containsPointInPlane(Vector(a + d * b)))
//		return d;
//	return INF;
//}
