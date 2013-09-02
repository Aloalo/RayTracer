#include "StdAfx.h"
#include "Scene.h"
#include "Essential.h"
#include <cmath>

Scene::Scene(void)
{
}

Scene::Scene(int maxDepth)
	: maxDepth(maxDepth), spaceIoR(1.0f)
{
}

Scene::~Scene(void)
{
	while(!objectList.empty())
	{
		delete objectList.back();
		objectList.pop_back();
	}
	while(!lightSourceList.empty())
	{
		delete lightSourceList.back();
		lightSourceList.pop_back();
	}
}

void Scene::render(OutputImage* output, int AALevel) const
{
	float angle = tan(efl::PI * 0.5 * output->fieldOfView / 180.0f);
	float invWidth = 1.0f / (float) output->width / AALevel;
	float invHeight = 1.0f / (float) output->height / AALevel;

	float from = -(float)AALevel / 2.0f + 1.0f;
	float to = (float)AALevel / 2.0f;
	for(int y = 0; y < AALevel * output->height; y += AALevel) 
		for(int x = 0; x < AALevel * output->width; x += AALevel)
		{
			Vector outColor(0.0f);
			for(float aay = from; !(aay > to); aay += 1.0f)
				for(float aax = from; !(aax > to); aax += 1.0f)
				{
					float xx = (2.0f * ((x + aax) * invWidth) - 1.0f) * angle * output->aspectRatio;
					float yy = (1.0f - 2.0f * ((y + aay) * invHeight)) * angle;
					Vector raydir(xx, yy, -1.0f);
					raydir.normalize();
					outColor += trace(Ray(Vector(0.0f), raydir), 1.0f, 0);
				}
				output->image[y * output->width / AALevel + x / AALevel] = outColor / (AALevel * AALevel);
		}
}

Vector Scene::trace(const Ray &r, float currentIoR, int depth) const
{
	float tnear = efl::INF;
	const IntersectableObject *obj = NULL;
	int objectListSize = objectList.size();

	for(int i = 0; i < objectListSize; ++i)
	{
		float t;
		if(objectList[i]->intersect(r, &t))
			if(t < tnear)
			{
				tnear = t;
				obj = objectList[i];
			}
	}

	if(!obj)
		return Vector(0.1f);


	Vector surfaceColor(1.0f);
	Vector phit = r.origin + r.direction * tnear;
	Vector nhit;
	obj->getNormalAtPoint(phit, nhit);
	
	float bias = 1e-4;
	float dotProd = dotProduct(r.direction, nhit);
	float ior = obj->ior;
	bool inside = false;

	if(dotProd > 0)
	{
		dotProd = -dotProd;
		nhit = -nhit;
		if(efl::abs(currentIoR - ior) < efl::ZERO)
			ior = spaceIoR;
		inside = true;
	}

	if((obj->transparency || obj->reflectivity) && depth < maxDepth)
	{
		Vector reflectionColor, refractionColor(0.0f);
		Vector refrdir(0.0f);

		Vector refldir = r.direction - nhit * 2 * dotProd;
		refldir.normalize();
		reflectionColor = trace(Ray(phit + nhit * bias, refldir), ior, depth + 1);

		if(obj->transparency)
		{
			Vector z = currentIoR / ior * (r.direction - dotProd * nhit);
			refrdir = z - sqrt(1 - z.length2()) * nhit;
			refrdir.normalize();
			refractionColor = trace(Ray(phit - nhit * bias, refrdir), ior, depth + 1);
		}

		float fresneleffect = efl::mix<float>(efl::pow(1.0f + dotProd, 3), 1.0f, 0.1f);

		surfaceColor = (reflectionColor * fresneleffect + refractionColor * (1 - fresneleffect));
	}

	if(obj->transparency <= efl::ZERO)
	{
		Vector lightContribution(0.0f);
		int lightSources = lightSourceList.size();
		for(int i = 0; i < lightSources; ++i)
		{
			Vector transmission(1.0f);
			Vector lightDirection = (lightSourceList[i]->position - phit).normalized();

			for(int j = 0; j < objectListSize; ++j)
			{
				float tmp;
				if (objectList[j]->intersect(Ray(phit + nhit * bias, lightDirection), &tmp))
				{
					transmission = 0.0f;
					if(objectList[j]->transparency)
						transmission = objectList[j]->color / 3.0f;
					break;
				}
			}
			lightContribution += transmission * 
				efl::max<float>(0.0f, dotProduct(lightDirection, nhit)) * lightSourceList[i]->intensityAtPoint(phit);
		}
		surfaceColor = surfaceColor * lightContribution;
	}
	return surfaceColor * obj->color;
}

void Scene::setMaxDepth(int depth)
{
	maxDepth = depth;
}

void Scene::addObject(IntersectableObject *obj)
{
	objectList.push_back(obj);
}

void Scene::addLightSource(LightSource *light)
{
	lightSourceList.push_back(light);
}
