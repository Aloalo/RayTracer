#pragma once

#include "Vector.h"

class OutputImage
{
public:
	OutputImage(int width, int height, float fieldOfView);
	~OutputImage(void);

	void saveToPPM(const char *path) const;

	int width, height;
	float fieldOfView;
	float aspectRatio;
	Vector *image;
};

