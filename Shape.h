#pragma once
#include "Coordinate.h"
#include <string>

class Shape
{
public:
	Shape(Coordinate*);
	virtual ~Shape(void);

	void setPosition(Coordinate*);
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
};

