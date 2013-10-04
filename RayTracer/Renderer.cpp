#include "StdAfx.h"
#include "Renderer.h"
#include "Essential.h"

Renderer::Renderer(int maxDepth)
	: maxDepth(maxDepth)
{
}


Renderer::~Renderer(void)
{
}

void Renderer::setMaxDepth(int depth)
{
	maxDepth = depth;
}


void Renderer::render(const Scene *tmpScenePtr, OutputImage* output, int AALevel)
{
	scene = tmpScenePtr;

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

	scene = NULL;
}

Vector Renderer::trace(const Ray &r, float currentIoR, int depth) const
{
	float tnear;
	IntersectableObject *obj = scene->hitObject(r, &tnear);
	if(obj == NULL)
		return scene->backgroundColor;

	Vector phit = r.origin + r.direction * tnear;
	Vector nhit;
	obj->getNormalAtPoint(phit, nhit);

	Vector outColor = scene->shade(r, obj->mat, nhit, phit);

	float dotProd = dotProduct(r.direction, nhit);
	float ior = obj->mat->ior;
	bool inside = false;

	if(dotProd > 0)
	{
		dotProd = -dotProd;
		nhit = -nhit;
		if(efl::abs(currentIoR - ior) < efl::ZERO)
			ior = scene->spaceIoR;
		inside = true;
	}

	if((obj->mat->transparency > efl::ZERO || obj->mat->reflectivity > efl::ZERO) && depth < maxDepth)
	{
		Vector reflectionColor(0.0f), refractionColor(0.0f);
		Vector refrdir(0.0f);

		Vector refldir = r.direction - nhit * 2 * dotProd;
		refldir.normalize();
		reflectionColor = trace(Ray(phit + nhit * efl::bias, refldir), ior, depth + 1) * obj->mat->color * obj->mat->reflectivity;

		if(obj->mat->transparency > efl::ZERO)
		{
			Vector z = currentIoR / ior * (r.direction - dotProd * nhit);
			refrdir = z - sqrt(1 - z.length2()) * nhit;
			refrdir.normalize();
			refractionColor = trace(Ray(phit - nhit * efl::bias, refrdir), ior, depth + 1);
			if(inside)
			{
				Vector absorbance = obj->mat->color * obj->mat->absorption * r.origin.distance(phit);
				Vector transparency = Vector(expf(absorbance.x), expf(absorbance.y), expf(absorbance.z));
				refractionColor = refractionColor * transparency;
			}
		}

		float fresneleffect = efl::mix<float>(efl::pow(1.0f + dotProd, 3), 1.0f, 0.1f);
		outColor += (reflectionColor * fresneleffect + refractionColor * (1 - fresneleffect));
	}

	return outColor;
}
