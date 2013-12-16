#pragma once

#include "Vec3.h"
//#include "Material.h"
//#include "Entity.h"
#include <string>
#include <math.h>

// Base class for xxxShape

class Shape
{
public:
	Shape(Vec3* offset = nullptr, Vec3* parentPos = nullptr);
	virtual ~Shape(void);

	//void setOwner(Entity*);

	void setPosition(Vec3*);

	//Entity* getOwner(void);
	Vec3* getPosition(void);

	//virtual float getArea(void) = 0;
	//virtual std::string getShapeType(void) = 0;

protected:
	Vec3* offset;
	Vec3* parentPos;
	//Entity* owner;
};

