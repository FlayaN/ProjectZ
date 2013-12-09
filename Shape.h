#pragma once
#include "Coordinate.h"
#include "Material.h"
#include <string>

class Shape
{
public:
	Shape(Coordinate*, int);
	virtual ~Shape(void);

	void setPosition(Coordinate*);
	void setPositionXYZ(float, float, float);
	void setPositionX(float);
	void setPositionY(float);
	void setPositionZ(float);

	void setSolid(bool);

	Coordinate* getPosition(void);
	float getPositionX(void);
	float getPositionY(void);
	float getPositionZ(void);

	virtual float getArea(void) = 0;
	virtual std::string getShapeType(void) = 0;

	virtual bool checkCollision(Shape*) = 0;

protected:
	Coordinate* position;
	int id;
};

