#pragma once

#include "Scene.h"
#include "OutputImage.h"

class Renderer
{
public:
	Renderer(int maxDepth);
	~Renderer(void);

	void render(const Scene *tmpScenePtr, OutputImage* output, int AALevel = 1, int numberOfThreads = 1);
	void setMaxDepth(int depth);

private:
	Vector trace(const Ray &r, float currentIoR, int depth) const;
	void threadRender(OutputImage* output, int AALevel, int firstRow, int lastRow);


	const Scene *scene;
	int maxDepth;
};

