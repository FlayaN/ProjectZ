#include "Material.h"


Material::Material(std::string labelIn = "unknown", float densityIn = 0.0)
{
	label = labelIn;
	density = densityIn;
}

Material::~Material(void)
{
}

//------------------------------------------------SET ----------------------------------------------//

void Material::setLabel(std::string labelIn)
{
	label = labelIn;
}

void Material::setDensity(float densityIn)
{
	density = densityIn;
}

//------------------------------------------------GET ----------------------------------------------//

std::string Material::getLabel(void)
{
	return label;
}

float Material::getDensity(void)
{
	return density;
}