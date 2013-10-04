#include "StdAfx.h"
#include "Scene.h"


Scene::Scene(const Vector &backgroundColor, float spaceIoR)
	: spaceIoR(spaceIoR), backgroundColor(backgroundColor)
{
}

Scene::~Scene(void)
{
}
