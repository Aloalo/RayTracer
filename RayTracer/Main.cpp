#include "stdafx.h"
#include "Scene.h"
#include "Sphere.h"
#include <ctime>

int _tmain(int argc, _TCHAR* argv[])
{
	int t = clock();

	Scene *scene = new Scene(10);
	//const Vector &color, float transparency, Float ior, float reflectivity, const Vector &center, float radius
	scene->addObject(new Sphere(Vector(0.2), false, 0.0f, false, Vector(0, -10004, -20), 10000));
	scene->addObject(new Sphere(Vector(1.0, 0.32, 0.36), true, 1.03f, true, Vector(0, 0, -20), 4));
	scene->addObject(new Sphere(Vector(1.0, 0.32, 0.36), false, 0.0f, true, Vector(0, 0, -20), 4));
	scene->addObject(new Sphere(Vector(0.90, 0.76, 0.46), false, 0.0f, true, Vector(5, -1, -15), 2));
	scene->addObject(new Sphere(Vector(1.0, 1.0, 0.5), false, 0.0f, true, Vector(5, 0, -25), 3));
	scene->addObject(new Sphere(Vector(1.0, 1.0, 0.5), true, 1.1f, true, Vector(-5.5, 0, -15), 3));

	scene->addLightSource(new LightSource(Vector(0, 10, -20), Vector(900.0f)));
	scene->addLightSource(new LightSource(Vector(0, 3, -10), Vector(600.0f)));

	OutputImage *image = new OutputImage(1920, 1080, 60.0f);
	scene->render(image, 32);
	image->saveToPPM("C:/Users/Jure/Desktop/untitled.ppm");

	delete scene;
	delete image;

	t = clock() - t;
	printf("It took me %d clicks (%f seconds).\n", t, ((float)t) / CLOCKS_PER_SEC);
	return 0;
}