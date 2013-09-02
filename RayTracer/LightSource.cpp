#include "StdAfx.h"
#include "LightSource.h"

LightSource::LightSource(const Vector &position, const Vector &intensity)
	: position(position), intensity(intensity), attenuationFactor(1.0f)
{
}

LightSource::LightSource(const Vector &position, const Vector &intensity, float attenFactor)
	: position(position), intensity(intensity), attenuationFactor(attenFactor)
{

}


LightSource::~LightSource(void)
{
}

Vector LightSource::intensityAtPoint(const Vector &p)
{
	return intensity / (attenuationFactor * position.distance2(p));
}
