#include "Shape.h"


Shape::Shape(Position* positionIn = NULL)
{
	position = positionIn;
}


Shape::~Shape(void)
{
	delete position;
}

//------------------------------------------------SET ----------------------------------------------//

void Shape::setPosition(Position* positionIn)
{
	delete position;
	position = positionIn;
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

Position* Shape::getPosition(void)
{
	return position;
}

//float getArea(void) = 0;
//std::string getShapeType(void) = 0;

//-----------------------------------------------CHECK----------------------------------------------//

//bool checkCollision(Shape*) = 0;