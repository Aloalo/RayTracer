#include "StdAfx.h"
#include "LightSource.h"

LightSource::LightSource(const Vector &position, const Vector &intensity)
	: position(position), intensity(intensity)
{
}


LightSource::~LightSource(void)
{
}
