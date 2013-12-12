#include "Shape.h"


Shape::Shape(Coordinate* positionIn = NULL, Entity* ownerIn = NULL)
{
	position = positionIn;
	owner = ownerIn;
}


Shape::~Shape(void)
{
	delete position;
}

//------------------------------------------------SET ----------------------------------------------//

void Shape::setOwner(Entity* ownerIn)
{
	delete owner;
	owner = ownerIn;
}

void Shape::setPosition(Coordinate* positionIn)
{
	delete position;
	position = positionIn;
}

void Shape::setPositionXYZ(float xIn, float yIn, float zIn)
{
	position->x = xIn;
	position->y = yIn;
	position->z = zIn;
}

void Shape::setPositionX(float xIn)
{
	position->x = xIn;
}

void Shape::setPositionY(float yIn)
{
	position->y = yIn;
}

void Shape::setPositionZ(float zIn)
{
	position->z = zIn;
}

//------------------------------------------------GET ----------------------------------------------//

Entity* Shape::getOwner(void)
{
	return owner;
}

float Shape::getPositionX(void)
{
	return position->x;
}

float Shape::getPositionY(void)
{
	return position->y;
}

float Shape::getPositionZ(void)
{
	return position->z;
}

Coordinate* Shape::getPosition(void)
{
	return position;
}

//float getArea(void) = 0;
//std::string getShapeType(void) = 0;