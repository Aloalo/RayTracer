#include "stdafx.h"
#include "Tracer.h"
#include "Sphere.h"
#include "Renderer.h"
#include <time.h>

int _tmain(int argc, _TCHAR* argv[])
{
	int t = clock();

	Tracer *tracer = new Tracer(10);
	//const Vector &color, float transparency, Float ior, float reflectivity, const Vector &center, float radius
	tracer->addObject(new Sphere(Vector(0.2), 0.0f, 0.0f, 0.0f, Vector(0, -10004, -20), 10000));
	tracer->addObject(new Sphere(Vector(1.0, 0.32, 0.36), 1.0f, 1.2f, 1.0f, Vector(0, 0, -20), 4));
	tracer->addObject(new Sphere(Vector(1.0, 0.32, 0.36), 0.0f, 0.0f, 1.0f, Vector(0, 0, -20), 4));
	tracer->addObject(new Sphere(Vector(0.90, 0.76, 0.46), 0.0f, 0.0f, 1.0f, Vector(5, -1, -15), 2));
	tracer->addObject(new Sphere(Vector(1.0, 1.0, 0.5), 0.0f, 0.0f, 1.0f, Vector(5, 0, -25), 3));
	tracer->addObject(new Sphere(Vector(1.0, 1.0, 0.5), 1.0f, 1.2f, 1.0f, Vector(-5.5, 0, -15), 3));

	tracer->addLightSource(new LightSource(Vector(0, 20, -30), Vector(3.0f)));
	tracer->addLightSource(new LightSource(Vector(0, 3, -10), Vector(5.0f)));

	Renderer renderer;
	OutputImage *image = new OutputImage(1920, 1080, 60.0f);
	renderer.render(tracer, image);
	image->saveToPPM("C:/Users/Jure/Desktop/untitled.ppm");

	delete tracer;
	delete image;

	t = clock() - t;
	printf("It took me %d clicks (%f seconds).\n", t, ((float)t) / CLOCKS_PER_SEC);
	return 0;
}