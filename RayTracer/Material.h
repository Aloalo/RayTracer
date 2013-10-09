#pragma once

#include "Vector.h"

class Material
{
public:
	Material(const Vector &color, float transparency, float ior, float absorption, float reflectivity, float diff, float spec, int shininess);
	Material(const Vector &color, float reflectivity, float diff, float spec, int shininess);
	Material(const Vector &color, float diff, float spec, int shininess);
	~Material(void);

	Vector color;
	float ior, absorption;
	float reflectivity, transparency;
	float diff, spec;
	int shininess;
};

