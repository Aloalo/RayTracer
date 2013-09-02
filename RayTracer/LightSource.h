#pragma once

#include "Vector.h"

class LightSource
{
public:
	LightSource(const Vector &position, const Vector &intensity);
	LightSource(const Vector &position, const Vector &intensity, float attenFactor);
	~LightSource(void);

	Vector intensityAtPoint(const Vector &p);

	float attenuationFactor;
	Vector position;
	Vector intensity;
};

