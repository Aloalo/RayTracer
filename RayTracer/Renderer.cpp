#include "StdAfx.h"
#include "Renderer.h"
#include "Essential.h"


Renderer::Renderer(void)
{
}


Renderer::~Renderer(void)
{
}

void Renderer::render(const Tracer *tracer, OutputImage* output, int AALevel) const
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
					outColor += tracer->trace(Ray(Vector(0.0f), raydir), 0);
				}
			output->image[y * output->width / AALevel + x / AALevel] = outColor / (AALevel * AALevel);
		}
}
