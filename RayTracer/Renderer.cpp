#include "StdAfx.h"
#include "Renderer.h"
#include "Essential.h"
#include <boost/thread/thread.hpp>

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


void Renderer::render(const Scene *tmpScenePtr, OutputImage* output, int AALevel, int numberOfThreads)
{
	scene = tmpScenePtr;

	std::vector<boost::thread> threads;
	int t = output->height / numberOfThreads;
	for(int i = 0; i < numberOfThreads; ++i)
	{
		if(i != numberOfThreads - 1)
			threads.push_back(boost::thread(boost::bind(&Renderer::threadRender, this, output, AALevel, i * t, (i + 1) * t)));
		else
			threads.push_back(boost::thread(boost::bind(&Renderer::threadRender, this, output, AALevel, i * t, output->height)));
	}
	for(int i = 0; i < numberOfThreads; ++i)
		threads[i].join();

	scene = NULL;
}

void Renderer::threadRender(OutputImage* output, int AALevel, int firstRow, int lastRow)
{
	float angle = tan(efl::PI * 0.5 * output->fieldOfView / 180.0f);
	float invWidth = 1.0f / (float) output->width / AALevel;
	float invHeight = 1.0f / (float) output->height / AALevel;

	float from = -(float)AALevel / 2.0f + 1.0f;
	float to = (float)AALevel / 2.0f;
	for(int y = firstRow * AALevel; y < AALevel * lastRow; y += AALevel) 
		for(int x = 0; x < AALevel * output->width; x += AALevel)
		{
			Vector outColor;
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
		Vector reflectionColor, refractionColor;
		Vector refrdir;

		Vector refldir = r.direction - nhit * 2 * dotProd;
		reflectionColor = trace(Ray(phit + nhit * efl::bias, refldir), ior, depth + 1) * obj->mat->color * obj->mat->reflectivity;

		if(obj->mat->transparency > efl::ZERO)
		{
			Vector z = currentIoR / ior * (r.direction - dotProd * nhit);
			refrdir = z - sqrt(1 - z.length2()) * nhit;
			refractionColor = trace(Ray(phit - nhit * efl::bias, refrdir), ior, depth + 1);
			if(inside)
			{
				Vector absorbance = obj->mat->color * obj->mat->absorption * r.origin.distance(phit);
				Vector transparency = Vector(expf(absorbance.x), expf(absorbance.y), expf(absorbance.z));
				refractionColor = refractionColor * transparency;
			}
		}

		float fresneleffect = efl::mix(efl::pow(1.0f + dotProd, 3), 1.0f, 0.1f);
		outColor += (reflectionColor * fresneleffect + (1 - fresneleffect) * refractionColor);
	}

	return outColor;
}
