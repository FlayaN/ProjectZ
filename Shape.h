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
	Shape(Vec2* posOffsetIn = nullptr, float rotOffsetIn = 0.0, T* ownerIn = nullptr);
	virtual ~Shape(void);

	void setOwner(T*);
	void setPosOffset(Vec2*);
	void setAbsPos(Vec2*);
	void setRotOffset(float);
	void setAbsRot(float);

	T* getOwner(void);
	Vec2 getPosOffset(void);
	Vec2 getAbsPos(void);
	float getRotOffset(void);
	float getAbsRot(void);

	//virtual float getArea(void) = 0;
	//virtual std::string getShapeType(void) = 0;

protected:
	Vec2* posOffset;
	float rotOffset;
	T* owner;
};

#endif