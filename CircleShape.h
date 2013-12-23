#pragma once

#include "shape.h"

#ifndef CIRCLESHAPE_H
#define CIRCLESHAPE_H

class CircleShape : protected Shape
{
public:
	CircleShape(Vec3* positionIn = nullptr, float radiusIn = 0.0);
	virtual ~CircleShape(void);

	void setRadius(float);

	float getRadius(void);
	float getArea(void);
	std::string getShapeType(void);

protected:
	float radius;
};

#endif