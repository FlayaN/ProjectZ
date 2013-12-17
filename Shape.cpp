#include "Shape.h"


Shape::Shape(Vec3* offsetIn, Vec3* parentPosIn)//, Entity* ownerIn = NULL)
{
	this->offset = offsetIn;
	this->parentPos = parentPosIn;
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

void Shape::setOffset(Vec3* offsetIn)
{
	delete offset;
	this->offset = offsetIn;
}

void Shape::setAbsPos(Vec3* absPosIn)
{
	delete offset;
	this->offset = new Vec3((*absPosIn)-(*parentPos));
}

//------------------------------------------------GET ----------------------------------------------//

/*Entity* Shape::getOwner(void)
{
	return owner;
}*/

Vec3 Shape::getOffset(void)
{
	return *offset;
}

Vec3 Shape::getAbsPos(void)
{
	return (*parentPos)+(*offset);
}

//float getArea(void) = 0;
//std::string getShapeType(void) = 0;