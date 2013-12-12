#include "CircleShape.h"


CircleShape::CircleShape(Coordinate* positionIn = NULL, float radiusIn = 0.0) : Shape(positionIn)
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
	return 4.0*M_PI*pow(radius, 3.0)/3.0;
}

std::string CircleShape::getShapeType(void)
{
	return "circle";
}