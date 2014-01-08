#pragma once

#include <string>
#include <math.h>

#include "lib/glm/vec2.hpp"
#include <SDL.h>

#ifndef SHAPE_H
#define SHAPE_H

template<class T>
class Shape
{
public:
	Shape(glm::vec2* posOffsetIn = nullptr, T* ownerIn = nullptr, float rotOffsetIn = 0.0);
	virtual ~Shape(void);

	void setOwner(T*);
	void setPosOffset(glm::vec2*);
	void setAbsPos(glm::vec2*);
	void setRotOffset(float);
	void setAbsRot(float);

	T* getOwner(void);
	glm::vec2 getPosOffset(void);
	glm::vec2 getAbsPos(void);
	float getRotOffset(void);
	float getAbsRot(void);

	//virtual float getArea(void) = 0;
	//virtual std::string getShapeType(void) = 0;

protected:
	glm::vec2* posOffset;
	float rotOffset;
	T* owner;
};



template<class T>
Shape<T>::Shape(glm::vec2* posOffsetIn, T* ownerIn, float rotOffsetIn)
{
	posOffset = posOffsetIn;
	rotOffset = rotOffsetIn;
	owner = ownerIn;
}

template<class T>
Shape<T>::~Shape(void)
{
	delete posOffset;	// delete owner separately
}

//------------------------------------------------SET ----------------------------------------------//

template<class T>
void Shape<T>::setOwner(T* ownerIn)
{
	owner = ownerIn;
}

template<class T>
void Shape<T>::setPosOffset(glm::vec2* posOffsetIn)
{
	delete posOffset;
	posOffset = posOffsetIn;
}

template<class T>
void Shape<T>::setAbsPos(glm::vec2* absPosIn)
{
	delete posOffset;
	posOffset = new glm::vec2((*absPosIn)-(*owner->getPosition()));
}

template<class T>
void Shape<T>::setRotOffset(float rotOffsetIn)
{
	rotOffset = rotOffsetIn;
}

template<class T>
void Shape<T>::setAbsRot(float absRotIn)
{
	rotOffset = absRotIn-(*owner->getRotation());
}

//------------------------------------------------GET ----------------------------------------------//

template<class T>
T* Shape<T>::getOwner(void)
{
	return owner;
}

template<class T>
glm::vec2 Shape<T>::getPosOffset(void)
{
	return *posOffset;
}

template<class T>
glm::vec2 Shape<T>::getAbsPos(void)
{
	return (*owner->getPosition())+(*posOffset);
}

template<class T>
float Shape<T>::getRotOffset(void)
{
	return rotOffset;
}

template<class T>
float Shape<T>::getAbsRot(void)
{
	return (*owner->getRotation())+rotOffset;
}

//float getArea(void) = 0;
//std::string getShapeType(void) = 0;

#endif