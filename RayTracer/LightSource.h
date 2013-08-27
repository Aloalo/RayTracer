#pragma once

#include "Vector.h"

class LightSource
{
public:
	LightSource(const Vector &position, const Vector &intensity);
	~LightSource(void);

	Vector position;
	Vector intensity;
};

