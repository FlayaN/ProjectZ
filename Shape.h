#pragma once
#include "Position.h"
#include <string>

class Shape
{
public:
	Shape(Position*);
	virtual ~Shape(void);

	void setPosition(Position*);
	void setPositionX(float);
	void setPositionY(float);
	void setPositionZ(float);

	Position* getPosition(void);
	float getPositionX(void);
	float getPositionY(void);
	float getPositionZ(void);

	virtual float getArea(void) = 0;
	virtual std::string getShapeType(void) = 0;

	virtual bool checkCollision(Shape*) = 0;

protected:
	Position* position;
};

