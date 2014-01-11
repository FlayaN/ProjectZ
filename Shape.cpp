#include "Shape.h"

Shape::Shape(glm::vec2* posOffsetIn, float rotOffsetIn)
{
	posOffset = posOffsetIn;
	rotOffset = rotOffsetIn;
}


Shape::~Shape(void)
{
	delete posOffset;	// delete owner separately
}

//------------------------------------------------SET ----------------------------------------------//

void Shape::setPosOffset(glm::vec2* posOffsetIn)
{
	delete posOffset;
	posOffset = posOffsetIn;
}

void Shape::setRotOffset(float rotOffsetIn)
{
	rotOffset = rotOffsetIn;
}

//------------------------------------------------GET ----------------------------------------------//

glm::vec2 Shape::getPosOffset(void)
{
	return *posOffset;
}

float Shape::getRotOffset(void)
{
	return rotOffset;
}

//float getArea(void) = 0;
//std::string getShapeType(void) = 0;
