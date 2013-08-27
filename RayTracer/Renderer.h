#pragma once

#include "OutputImage.h"
#include "Tracer.h"

class Renderer
{
public:
	Renderer(void);
	~Renderer(void);

	void render(const Tracer *tracer, OutputImage* output, int AAlevel = 1) const;
};

