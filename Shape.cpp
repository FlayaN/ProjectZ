#include "Shape.h"


Shape::Shape(Coordinate* positionIn)//, Entity* ownerIn = NULL)
{
	position = positionIn;
	//owner = ownerIn;
}


Shape::~Shape(void)
{
	delete position;
}

//------------------------------------------------SET ----------------------------------------------//

/*void Shape::setOwner(Entity* ownerIn)
{
	delete owner;
	owner = ownerIn;
}*/

void Shape::setPosition(Coordinate* positionIn)
{
	delete position;
	position = positionIn;
}

//------------------------------------------------GET ----------------------------------------------//

/*Entity* Shape::getOwner(void)
{
	return owner;
}*/

Coordinate* Shape::getPosition(void)
{
	return position;
}

//float getArea(void) = 0;
//std::string getShapeType(void) = 0;