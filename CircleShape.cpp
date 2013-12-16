#include "CircleShape.h"


CircleShape::CircleShape(Coordinate* positionIn, float radiusIn) : Shape(positionIn)
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