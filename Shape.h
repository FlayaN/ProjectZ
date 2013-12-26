#pragma once

#include <string>
#include <math.h>

#include "Vec3.h"

#ifndef SHAPE_H
#define SHAPE_H

template<class T>
class Shape
{
public:
	Shape(Vec2* offsetIn = nullptr, T* ownerIn = nullptr);
	virtual ~Shape(void);

	void setOwner(T*);
	void setOffset(Vec2*);
	void setAbsPos(Vec2*);

	T* getOwner(void);
	Vec2 getOffset(void);
	Vec2 getAbsPos(void);

	//virtual float getArea(void) = 0;
	//virtual std::string getShapeType(void) = 0;

protected:
	Vec2* offset;
	T* owner;
};

#endif