#include "StdAfx.h"
#include "SlowScene.h"
#include "Essential.h"
#include <cmath>


SlowScene::SlowScene(const Vector &backgroundColor, float spaceIoR)
	: Scene(backgroundColor, spaceIoR)
{
}

SlowScene::~SlowScene(void)
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

void SlowScene::addObject(IntersectableObject *obj)
{
	objectList.push_back(obj);
}

void SlowScene::addLightSource(LightSource *light)
{
	lightSourceList.push_back(light);
}

IntersectableObject* SlowScene::hitObject(const Ray &r, float *distance) const
{
	*distance = efl::INF;
	int objectListSize = objectList.size();
	IntersectableObject *obj = NULL;

	for(int i = 0; i < objectListSize; ++i)
	{
		float t;
		if(objectList[i]->intersect(r, &t))
			if(t < *distance)
			{
				*distance = t;
				obj = objectList[i];
			}
	}

	return obj;
}

Vector SlowScene::shade(const Ray &r, const Material *mat, const Vector &nhit, const Vector &phit) const
{
	Vector outColor(0.0f);
	int objectListSize = objectList.size();
	float tnear = (phit - r.origin).length();

	int lightSources = lightSourceList.size();
	for(int i = 0; i < lightSources; ++i)
	{
		float transmission(1.0f);
		Vector lightDirection = (lightSourceList[i]->position - phit).normalized();

		for(int j = 0; j < objectListSize; ++j)
		{
			float tmp;
			if (objectList[j]->intersect(Ray(phit + nhit * efl::bias, lightDirection), &tmp) && tmp < tnear)
			{
				transmission = 0.0f;
				break;
			}
		}
		if(transmission > efl::ZERO)//shade
		{
			Vector lightIntensity = lightSourceList[i]->intensityAtPoint(phit);
			if(mat->diff > efl::ZERO)//diffuse
				outColor += efl::max<float>(0.0f, dotProduct(lightDirection, nhit))
				* lightIntensity * mat->color * mat->diff;
			if(mat->spec > efl::ZERO)//specular
			{
				Vector R = lightDirection - 2.0f * dotProduct(lightDirection, nhit) * nhit;
				float dot = dotProduct(r.direction , R.normalized());
				if (dot > 0)
				{
					float spec = efl::pow(dot, 20) * mat->spec;
					outColor += spec * lightIntensity * mat->color;
				}
			}
		}
	}
	return outColor;
}
