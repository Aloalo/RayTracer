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

const Vector& LightSource::intensityAtPoint(const Vector &p) const
{
	return intensity / (attenuationFactor * position.distance2(p));
}
