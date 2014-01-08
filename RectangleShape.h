#pragma once

#ifndef RECTANGLESHAPE_H
#define RECTANGLESHAPE_H

#include <vector>

#include "Shape.h"
#include "lib/glm/vec2.hpp"


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
	
	float* getVertexArray(void);
	float* getTexCoordArray(void);
	float* getNormalArray(void);
	int* getIndexArray(void);
	float* getColorArray(void);

	int getNumVertices(void);
	int getNumIndices(void);


private:
	glm::vec2* size;
	SDL_Surface* surface;

	std::vector<glm::vec2> vertexArray;
	std::vector<glm::vec2> texCoordArray;
	std::vector<glm::vec2> normalArray;
	std::vector<glm::ivec2> indexArray;
	std::vector<glm::vec2> colorArray;
};

template<class T>
RectangleShape<T>::RectangleShape(glm::vec2* posOffsetIn, T* ownerIn, glm::vec2* sizeIn, std::string tex) : Shape<T>(posOffsetIn, ownerIn)
{

	size = sizeIn;
	surface = TextureManager::getInstance().getSurface(tex);
	glm::vec2 min(posOffsetIn->x - sizeIn->x / 2.0, posOffsetIn->y - sizeIn->y / 2.0);
	glm::vec2 max(posOffsetIn->x + sizeIn->x / 2.0, posOffsetIn->y + sizeIn->y / 2.0);

	vertexArray.push_back(glm::vec2(min.x, min.y));
	vertexArray.push_back(glm::vec2(min.x, max.y));
	vertexArray.push_back(glm::vec2(max.x, min.y));
	vertexArray.push_back(glm::vec2(max.x, min.y));
	vertexArray.push_back(glm::vec2(min.x, max.y));
	vertexArray.push_back(glm::vec2(max.x, max.y));

	texCoordArray.push_back(glm::vec2(0.0f, 1.0f));
	texCoordArray.push_back(glm::vec2(0.0f, 0.0f));
	texCoordArray.push_back(glm::vec2(1.0f, 1.0f));
	texCoordArray.push_back(glm::vec2(1.0f, 1.0f));
	texCoordArray.push_back(glm::vec2(0.0f, 0.0f));
	texCoordArray.push_back(glm::vec2(1.0f, 0.0f));
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

template<class T>
float* RectangleShape<T>::getVertexArray(void)
{
	if(vertexArray.size() == 0)
		return nullptr;
	return &vertexArray[0].x;
}

template<class T>
float* RectangleShape<T>::getTexCoordArray(void)
{
	if(texCoordArray.size() == 0)
		return nullptr;
	return &texCoordArray[0].x;
}

template<class T>
float* RectangleShape<T>::getNormalArray(void)
{
	if(normalArray.size() == 0)
		return nullptr;
	return &normalArray[0].x;
}

template<class T>
int* RectangleShape<T>::getIndexArray(void)
{
	if(indexArray.size() == 0)
		return nullptr;
	return &indexArray[0].x;
}

template<class T>
float* RectangleShape<T>::getColorArray(void)
{
	if(colorArray.size() == 0)
		return nullptr;
	return &colorArray[0].x;
}

template<class T>
int RectangleShape<T>::getNumVertices(void)
{
	return vertexArray.size();
}

template<class T>
int RectangleShape<T>::getNumIndices(void)
{
	return indexArray.size();
}

#endif