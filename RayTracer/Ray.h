#pragma once

#include "Vector.h"
//#include "Surfaces.h"

class Ray
{
public:
	Vector origin, direction;

	Ray(void);
	Ray(const Vector &origin, const Vector &direction);
	~Ray(void);

	/*double hit(Surface *sf) const;
	double hit(const Plane &pi) const;
	double hit(const Triangle &t) const;
	double hit(const SquareAA &sq) const;
	double hit(const RectangleAA &sq) const;*/
};