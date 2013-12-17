#include "Shape.h"


Shape::Shape(Vec3* offset, Vec3* parentPos)//, Entity* ownerIn = NULL)
{
	this->offset = offset;
	this->parentPos = parentPos;
	//position = positionIn;
	//owner = ownerIn;
}


Shape::~Shape(void)
{
	delete offset;
	delete parentPos;
}

//------------------------------------------------SET ----------------------------------------------//

/*void Shape::setOwner(Entity* ownerIn)
{
	delete owner;
	owner = ownerIn;
}*/

void Shape::setPosition(Vec3* positionIn)
{
	delete offset;
	this->offset = offset;
}

//------------------------------------------------GET ----------------------------------------------//

/*Entity* Shape::getOwner(void)
{
	return owner;
}*/

Vec3 Shape::getPosition(void)
{
	return (*parentPos)+(*offset);
}

//float getArea(void) = 0;
//std::string getShapeType(void) = 0;