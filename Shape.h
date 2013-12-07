#pragma once
#include "Coordinate.h"
#include <string>
#include <algorithm>

class Shape
{
public:
	Shape(Coordinate*, bool);
	virtual ~Shape(void);

	void setPosition(Coordinate*);
	void setPositionXYZ(float, float, float);
	void setPositionX(float);
	void setPositionY(float);
	void setPositionZ(float);

	Coordinate* getPosition(void);
	float getPositionX(void);
	float getPositionY(void);
	float getPositionZ(void);

	virtual float getArea(void) = 0;
	virtual std::string getShapeType(void) = 0;

	virtual bool checkCollision(Shape*) = 0;

protected:
	Coordinate* position;
	bool solid;
};

