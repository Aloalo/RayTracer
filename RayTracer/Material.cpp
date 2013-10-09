#include "StdAfx.h"
#include "Material.h"

Material::Material(const Vector &color, float transparency, float ior, 
	float absorption, float reflectivity, float diff, float spec, int shininess)
	: color(color), ior(ior), reflectivity(reflectivity), 
	transparency(transparency), diff(diff), spec(spec), absorption(absorption), shininess(shininess)
{
}

Material::Material(const Vector &color, float reflectivity, float diff, float spec, int shininess)
	: color(color), ior(0.0f), reflectivity(reflectivity), transparency(0.0f), diff(diff), spec(spec), absorption(0.0f), shininess(shininess)
{
}

Material::Material(const Vector &color, float diff, float spec, int shininess)
	: color(color), ior(0.0f), reflectivity(0.0f), transparency(0.0f), diff(diff), spec(spec), absorption(0.0f), shininess(shininess)
{

}


Material::~Material(void)
{
}
