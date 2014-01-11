#include "RectangleShape.h"

RectangleShape::RectangleShape(glm::vec2* posOffsetIn, float rotOffsetIn, glm::vec2* sizeIn, std::string tex) : Shape(posOffsetIn, rotOffsetIn)
{
	size = sizeIn;
	surface = TextureManager::getInstance().getSurface(tex);
}

RectangleShape::~RectangleShape(void)
{
}

//------------------------------------------------SET ----------------------------------------------//

void RectangleShape::setWidth(float widthIn)
{
	size->x = widthIn;
}

void RectangleShape::setHeight(float heightIn)
{
	size->y = heightIn;
}

//------------------------------------------------GET ----------------------------------------------//

float RectangleShape::getWidth(void)
{
	return size->x;
}

float RectangleShape::getHeight(void)
{
	return size->y;
}

float RectangleShape::getArea(void)
{
	return size->x*size->y;
}

std::string RectangleShape::getShapeType(void)
{
	return "rectangle";
}

SDL_Surface* RectangleShape::getSurface(void)
{
	return surface;
}