#pragma once

#define _USE_MATH_DEFINES

#include "Coordinate.h"
#include "Material.h"
#include "Entity.h"
#include <string>
#include <math.h> 

// Base class for xxxShape

class Shape
{
public:
	Shape(Coordinate*, Entity*);
	virtual ~Shape(void);

	void setOwner(Entity*);
	void setPosition(Coordinate*);
	void setPositionXYZ(float, float, float);
	void setPositionX(float);
	void setPositionY(float);
	void setPositionZ(float);

	Entity* getOwner(void);
	Coordinate* getPosition(void);
	float getPositionX(void);
	float getPositionY(void);
	float getPositionZ(void);

	virtual float getArea(void) = 0;
	virtual std::string getShapeType(void) = 0;

protected:
	Coordinate* position;
	Entity* owner;
};

