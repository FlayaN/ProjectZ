#pragma once

#include "Shape.h"

#ifndef CIRCLESHAPE_H
#define CIRCLESHAPE_H

template<class T>
class CircleShape : protected Shape<T>
{
public:
	CircleShape(glm::vec2* posOffsetIn = nullptr, T* ownerIn = nullptr, float radiusIn = 1.0f);
	virtual ~CircleShape(void);

	void setRadius(float);

	float getRadius(void);
	float getArea(void);
	std::string getShapeType(void);

protected:
	float radius;
};



template<class T>
CircleShape<T>::CircleShape(glm::vec2* posOffsetIn, T* ownerIn, float radiusIn) : Shape<T>(posOffsetIn, ownerIn)
{
	radius = radiusIn;
}

template<class T>
CircleShape<T>::~CircleShape(void)
{
}

//------------------------------------------------SET ----------------------------------------------//

template<class T>
void CircleShape<T>::setRadius(float radiusIn)
{
	radius = radiusIn;
}

//------------------------------------------------GET ----------------------------------------------//

template<class T>
float CircleShape<T>::getRadius(void)
{
	return radius;
}

template<class T>
float CircleShape<T>::getArea(void)
{
	return 4.0*3.14*pow(radius, 3.0)/3.0;
}

template<class T>
std::string CircleShape<T>::getShapeType(void)
{
	return "circle";
}

#endif