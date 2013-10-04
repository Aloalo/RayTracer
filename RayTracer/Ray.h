#pragma once

#include "Vector.h"

class Ray
{
public:
	Ray(void);
	Ray(const Vector &origin, const Vector &direction);
	~Ray(void);

	Vector origin, direction;
	/*double hit(Surface *sf) const;
	double hit(const Plane &pi) const;
	double hit(const Triangle &t) const;
	double hit(const SquareAA &sq) const;
	double hit(const RectangleAA &sq) const;*/
};