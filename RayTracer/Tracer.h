#pragma once

#include "IntersectableObject.h"
#include "LightSource.h"
#include <vector>

class Tracer
{
public:
	Tracer(void);
	Tracer(int maxDepth);
	~Tracer(void);

	Vector trace(const Ray& r, float currentIoR, int depth) const;

	void setMaxDepth(int depth);
	void addObject(IntersectableObject *obj);
	void addLightSource(LightSource *light);

private:
	std::vector<IntersectableObject*> objectList;
	std::vector<LightSource*> lightSourceList;
	int maxDepth;
};

