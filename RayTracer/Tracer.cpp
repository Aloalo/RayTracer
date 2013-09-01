#include "StdAfx.h"
#include "Tracer.h"
#include "Essential.h"

Tracer::Tracer(void)
{
}

Tracer::Tracer(int maxDepth)
	: maxDepth(maxDepth)
{
}

Tracer::~Tracer(void)
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

Vector Tracer::trace(const Ray &r, float currentIoR, int depth) const
{
	float tnear = efl::INF;
	const IntersectableObject *obj = NULL;
	int objectListSize = objectList.size();

	for(int i = 0; i < objectListSize; ++i)
	{
		float t;
		if(objectList[i]->intersect(r, &t))
		{
			if (t < tnear)
			{
				tnear = t;
				obj = objectList[i];
			}
		}
	}

	if(!obj)
		return Vector(2.0f);

	Vector surfaceColor(0);
	Vector phit = r.origin + r.direction * tnear;
	Vector nhit;
	obj->getNormalAtPoint(phit, nhit);
	
	float bias = 1e-4;
	float dotProd = dotProduct(r.direction, nhit);

	if(dotProd > 0)
	{
		dotProd = -dotProd;
		nhit = -nhit;
	}

	if((obj->transparency > efl::ZERO || obj->reflectivity > efl::ZERO) && depth < maxDepth)
	{
		Vector reflectionColor, refractionColor(0.0f);
		Vector refrdir(0.0f);

		if(obj->reflectivity > efl::ZERO)
		{
			Vector refldir = r.direction - nhit * 2 * dotProd;
			refldir.normalize();
			reflectionColor = trace(Ray(phit + nhit * bias, refldir), obj->ior, depth + 1);
		}

		if(obj->transparency > efl::ZERO)
		{
			Vector z = currentIoR / obj->ior * (r.direction - dotProd * nhit);
			refrdir = z - sqrt(1 - z.length2()) * nhit;
			refrdir.normalize();
			refractionColor = trace(Ray(phit - nhit * bias, refrdir), obj->ior, depth + 1);
		}

		float fresneleffect = efl::mix<float>(efl::pow(1.0f + dotProd, 3), 1.0f, 0.1f);

		/*float dotProd2 = dotProduct(nhit, refrdir);
		float par = (obj->ior * dotProd - currentIoR * dotProd2) / (obj->ior * dotProd + currentIoR * dotProd2);
		float perp = (currentIoR * dotProd - obj->ior * dotProd2) / (currentIoR * dotProd + obj->ior * dotProd2);
		float fresneleffect = (par * par + perp * perp) / 2.0f;*/

		surfaceColor = (reflectionColor * fresneleffect + refractionColor * (1 - fresneleffect)) * obj->color;
	}
	else
	{
		int lightSources = lightSourceList.size();
		for(int i = 0; i < lightSources; ++i)
		{
			float transmission = 1;
			Vector lightDirection = (lightSourceList[i]->position - phit).normalized();

			for(int j = 0; j < objectListSize; ++j)
			{
				float tmp;
				if (objectList[j]->intersect(Ray(phit + nhit * bias, lightDirection), &tmp))
				{
					transmission = 0;
					break;
				}
			}
			surfaceColor += obj->color * transmission * 
				efl::max<float>(0.0f, dotProduct(lightDirection, nhit)); //* lightSourceList[i]->intensity;
		}
	}
	return surfaceColor;
}

void Tracer::setMaxDepth(int depth)
{
	maxDepth = depth;
}

void Tracer::addObject(IntersectableObject *obj)
{
	objectList.push_back(obj);
}

void Tracer::addLightSource(LightSource *light)
{
	lightSourceList.push_back(light);
}
