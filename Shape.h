#pragma once

#include "Coordinate.h"
//#include "Material.h"
//#include "Entity.h"
#include <string>
#include <math.h>

// Base class for xxxShape

class Shape
{
public:
	Shape(Coordinate* positionIn = nullptr);
	virtual ~Shape(void);

	//void setOwner(Entity*);
	void setPosition(Coordinate*);

	//Entity* getOwner(void);
	Coordinate* getPosition(void);

	virtual float getArea(void) = 0;
	virtual std::string getShapeType(void) = 0;

protected:
	Coordinate* position;
	//Entity* owner;
};

