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

Vector Tracer::trace(const Ray &r, int depth) const
{
	float tnear = efl::INF;
	const IntersectableObject *obj = NULL;
	int objectListSize = objectList.size();

	for (int i = 0; i < objectListSize; ++i)
	{
		float t;
		if (objectList[i]->intersect(r, &t))
		{
			if (t < tnear)
			{
				tnear = t;
				obj = objectList[i];
			}
		}
	}

	if (!obj)
		return Vector(2.0f);

	Vector surfaceColor(0);
	Vector phit = r.origin + r.direction * tnear;
	Vector nhit;
	obj->getNormalAtPoint(phit, nhit);
	
	float bias = 1e-4;
	bool inside = false;
	float dotProd = dotProduct(r.direction, nhit);

	if (dotProd > 0)
	{
		dotProd = -dotProd;
		nhit = -nhit;
		inside = true;
	}

	if ((obj->transparency > efl::ZERO || obj->reflectivity > efl::ZERO) && depth < maxDepth)
	{
		Vector reflection, refraction(0.0f);

		if(obj->reflectivity > efl::ZERO)
		{
			Vector refldir = r.direction - nhit * 2 * dotProd;
			refldir.normalize();
			reflection = trace(Ray(phit + nhit * bias, refldir), depth + 1);
		}

		if (obj->transparency > efl::ZERO)
		{
			float ior = 1.1, eta = (inside) ? ior : 1 / ior;
			float cosi = -dotProd;
			float k = 1 - eta * eta * (1 - cosi * cosi);
			Vector refrdir = r.direction * eta + nhit * (eta *  cosi - sqrt(k));
			refrdir.normalize();
			refraction = trace(Ray(phit - nhit * bias, refrdir), depth + 1);
		}

		float facingratio = -dotProd;
		float fresneleffect = efl::mix<float>(efl::pow(1.0f - facingratio, 3), 1.0f, 0.1f);

		surfaceColor = (reflection * fresneleffect + 
			refraction * (1 - fresneleffect) * obj->transparency) * obj->color;
	}
	else
	{
		int lightSources = lightSourceList.size();
		for (int i = 0; i < lightSources; ++i)
		{
			Vector transmission = 1;
			Vector lightDirection = (lightSourceList[i]->position - phit).normalized();

			for (int j = 0; j < objectListSize; ++j)
			{
				float tmp;
				if (objectList[j]->intersect(Ray(phit + nhit * bias, lightDirection), &tmp))
				{
					transmission = 0;
					break;
				}
			}
			surfaceColor += obj->color * transmission * 
				efl::max<float>(0.0f, dotProduct(lightDirection, nhit)) * lightSourceList[i]->intensity;
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
