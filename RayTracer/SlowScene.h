#pragma once

#include <vector>
#include "Scene.h"

class SlowScene
	: public Scene
{
public:
	SlowScene(const Vector &backgroundColor, float spaceIoR);
	~SlowScene(void);

	void addObject(IntersectableObject *obj);
	void addLightSource(LightSource *light);

	IntersectableObject* hitObject(const Ray &r, float *distance) const;
	Vector shade(const Ray &r, const Material *mat, const Vector &nhit, const Vector &phit) const;

private:
	std::vector<IntersectableObject*> objectList;
	std::vector<LightSource*> lightSourceList;
};

