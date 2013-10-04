#pragma once

#include "IntersectableObject.h"
#include "LightSource.h"

class Scene
{
public:
	Scene(const Vector &backgroundColor, float spaceIoR);
	virtual ~Scene(void);

	virtual void addObject(IntersectableObject *obj) = 0;
	virtual void addLightSource(LightSource *light) = 0;

	virtual IntersectableObject* hitObject(const Ray &r, float *distance) const = 0;
	virtual Vector shade(const Ray &r, const Material *mat, const Vector &nhit, const Vector &phit) const = 0;

	const float spaceIoR;
	const Vector backgroundColor;
};

