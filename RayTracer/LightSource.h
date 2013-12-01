#pragma once

#include "Vector.h"

class LightSource
{
public:
	LightSource(const Vector &position, const Vector &intensity);
	LightSource(const Vector &position, const Vector &intensity, float attenFactor);
	~LightSource(void);

	const Vector& intensityAtPoint(const Vector &p) const;

	float attenuationFactor;
	Vector position;
	Vector intensity;
};

