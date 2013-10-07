#include "stdafx.h"
#include "SlowScene.h"
#include "Sphere.h"
#include <ctime>
#include "Material.h"
#include "Plane.h"
#include "OutputImage.h"
#include "Renderer.h"

int _tmain(int argc, _TCHAR* argv[])
{
	int t = clock();

	Scene *scene = new SlowScene(Vector(0.8, 0.8, 0.8), 1.0f);

	scene->addObject(new Plane(new Material(Vector(1.0f), 1.0f, 0.1f, 0.1f), Vector(0.0f, 1.0f, 0.0f), Vector(0.0f, -5.0f, 0.0f)));
	scene->addObject(new Plane(new Material(Vector(1.0, 1.0, 1.0), 1.0f, 0.0f), Vector(0.0f, 0.0f, 1.0f), Vector(0.0f, 0.0f, -40.0f)));
	scene->addObject(new Plane(new Material(Vector(1.0, 1.0, 1.0), 1.0f, 0.0f), Vector(0.0f, 0.0f, -1.0f), Vector(0.0f, 0.0f, 5.0f)));
	scene->addObject(new Plane(new Material(Vector(1.0, 1.0, 1.0), 1.0f, 0.0f), Vector(0.0f, -1.0f, 0.0f), Vector(0.0f, 15.0f, 0.0f)));
	scene->addObject(new Plane(new Material(Vector(1.0, 1.0, 1.0), 1.0f, 0.0f), Vector(-1.0f, 0.0f, 0.0f), Vector(25.0f, 0.0f, 0.0f)));
	scene->addObject(new Plane(new Material(Vector(1.0, 1.0, 1.0), 1.0f, 0.0f), Vector(1.0f, 0.0f, 0.0f), Vector(-25.0f, 0.0f, 0.0f)));

	scene->addObject(new Sphere(new Material(Vector(1.0, 1.0, 1.0), 1.0f, 1.33f, 1.0f, 0.1f, 0.9f, 0.05f), Vector(15, 0, -25), 4));
	scene->addObject(new Sphere(new Material(Vector(1.0, 0.32, 0.36), 1.0f, 0.8f), Vector(0, 0, -20), 4));
	scene->addObject(new Sphere(new Material(Vector(1.0f), 1.0f, 0.0f, 1.0f), Vector(5, -1, -15), 2));
	scene->addObject(new Sphere(new Material(Vector(1.0, 1.0, 0.5), 1.0f, 1.2f, 1.0f, 0.1f, 0.9f, 0.01), Vector(-5.5, 0, -15), 3));

	scene->addLightSource(new LightSource(Vector(10, 10, -20), Vector(100.0f)));
	scene->addLightSource(new LightSource(Vector(0, 3, -10), Vector(30.0f)));
	scene->addLightSource(new LightSource(Vector(0, 3, 10), Vector(100.0f)));

	OutputImage *image = new OutputImage(1920, 1080, 60.0f);
	Renderer renderer(5);
	renderer.render(scene, image);
	image->saveToPPM("C:/Users/Jure/Desktop/untitled.ppm");

	delete scene;
	delete image;

	t = clock() - t;
	printf("It took me %d clicks (%f seconds).\n", t, ((float)t) / CLOCKS_PER_SEC);
	return 0;
}