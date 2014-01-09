#pragma once

#ifndef RECTANGLESHAPE_H
#define RECTANGLESHAPE_H

#include <vector>

#include "Shape.h"


template<class T>
class RectangleShape : protected Shape<T>
{
public:
	RectangleShape(glm::vec2* posOffsetIn = nullptr, T* ownerIn = nullptr, glm::vec2* sizeIn = new glm::vec2(), std::string tex = "default");
	virtual ~RectangleShape(void);

	void setWidth(float);
	void setHeight(float);

	float getWidth(void);
	float getHeight(void);
	float getArea(void);
	std::string getShapeType(void);
	SDL_Surface* getSurface(void);

private:

	glm::vec2* size;
	SDL_Surface* surface;
};

template<class T>
RectangleShape<T>::RectangleShape(glm::vec2* posOffsetIn, T* ownerIn, glm::vec2* sizeIn, std::string tex) : Shape<T>(posOffsetIn, ownerIn)
{
	size = sizeIn;
	surface = TextureManager::getInstance().getSurface(tex);
}

template<class T>
RectangleShape<T>::~RectangleShape(void)
{
}

//------------------------------------------------SET ----------------------------------------------//

template<class T>
void RectangleShape<T>::setWidth(float widthIn)
{
	size->x = widthIn;
}

template<class T>
void RectangleShape<T>::setHeight(float heightIn)
{
	size->y = heightIn;
}

//------------------------------------------------GET ----------------------------------------------//

template<class T>
float RectangleShape<T>::getWidth(void)
{
	return size->x;
}

template<class T>
float RectangleShape<T>::getHeight(void)
{
	return size->y;
}

template<class T>
float RectangleShape<T>::getArea(void)
{
	return size->x*size->y;
}

template<class T>
std::string RectangleShape<T>::getShapeType(void)
{
	return "rectangle";
}

template<class T>
SDL_Surface* RectangleShape<T>::getSurface(void)
{
	return surface;
}

#endif