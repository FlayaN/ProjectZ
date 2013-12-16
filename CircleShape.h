#pragma once
#include "shape.h"

class CircleShape : protected Shape
{
public:
	CircleShape(Coordinate* positionIn = nullptr, float radiusIn = 0.0);
	virtual ~CircleShape(void);

	void setRadius(float);

	float getRadius(void);
	float getArea(void);
	std::string getShapeType(void);

protected:
	float radius;
};

