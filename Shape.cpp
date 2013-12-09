#include "Shape.h"


Shape::Shape(Coordinate* positionIn = NULL, int idIn = NULL)
{
	position = positionIn;
	id = idIn;
}


Shape::~Shape(void)
{
	delete position;
}

//------------------------------------------------SET ----------------------------------------------//

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

//-----------------------------------------------CHECK----------------------------------------------//

//bool checkCollision(Shape*) = 0;