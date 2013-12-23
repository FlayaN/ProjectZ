#pragma once

#include <string>
#include <math.h>

#include "Vec3.h"
//#include "Material.h"
//#include "Entity.h"

#ifndef SHAPE_H
#define SHAPE_H

class Shape
{
public:
	Shape(Vec3* offsetIn = nullptr, Vec3* parentPosIn = nullptr);
	virtual ~Shape(void);

	//void setOwner(Entity*);
	void setOffset(Vec3*);
	void setAbsPos(Vec3*);

	//Entity* getOwner(void);
	Vec3 getOffset(void);
	Vec3 getAbsPos(void);

	//virtual float getArea(void) = 0;
	//virtual std::string getShapeType(void) = 0;

protected:
	Vec3* offset;
	Vec3* parentPos;
	//Entity* owner;
};

#endif