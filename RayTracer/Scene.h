#pragma once

#include "IntersectableObject.h"
#include "LightSource.h"
#include "OutputImage.h"
#include <vector>

class Scene
{
public:
	Scene(void);
	Scene(int maxDepth);
	~Scene(void);

	void setMaxDepth(int depth);
	void addObject(IntersectableObject *obj);
	void addLightSource(LightSource *light);
	void render(OutputImage* output, int AALevel = 1) const;

private:
	Vector trace(const Ray& r, float currentIoR, int depth) const;

	std::vector<IntersectableObject*> objectList;
	std::vector<LightSource*> lightSourceList;
	int maxDepth;
	float spaceIoR;
};

