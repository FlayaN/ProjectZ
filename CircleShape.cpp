#include "CircleShape.h"

CircleShape::CircleShape(glm::vec2* posOffsetIn, float rotOffsetIn, float radiusIn) : Shape(posOffsetIn, rotOffsetIn)
{
	radius = radiusIn;
}

CircleShape::~CircleShape(void)
{
}

//------------------------------------------------SET ----------------------------------------------//

void CircleShape::setRadius(float radiusIn)
{
	radius = radiusIn;
}

//------------------------------------------------GET ----------------------------------------------//

float CircleShape::getRadius(void)
{
	return radius;
}

float CircleShape::getArea(void)
{
	return 4.0*3.14*pow(radius, 3.0)/3.0;
}

std::string CircleShape::getShapeType(void)
{
	return "circle";
}