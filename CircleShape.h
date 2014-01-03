#pragma once

#include "shape.h"

#ifndef CIRCLESHAPE_H
#define CIRCLESHAPE_H

template<class T>
class CircleShape : protected Shape<T>
{
public:
	CircleShape(Vec3* positionIn = nullptr, T* ownerIn = nullptr, float radiusIn = 1.0f);
	virtual ~CircleShape(void);

	void setRadius(float);

	float getRadius(void);
	float getArea(void);
	std::string getShapeType(void);

protected:
	float radius;
};

#endif