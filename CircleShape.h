#pragma once

#include "Shape.h"

#ifndef CIRCLESHAPE_H
#define CIRCLESHAPE_H

class CircleShape : protected Shape
{
public:
	CircleShape(glm::vec2* posOffsetIn = nullptr, float rotOffsetIn = 0.0f, float radiusIn = 1.0f);
	virtual ~CircleShape(void);

	void setRadius(float);

	float getRadius(void);
	float getArea(void);
	std::string getShapeType(void);

protected:
	float radius;
};

#endif