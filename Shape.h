#pragma once

#include <string>
#include <math.h>

#include "lib/glm/vec2.hpp"

#ifndef SHAPE_H
#define SHAPE_H

template<class T>
class Shape
{
public:
	Shape(glm::vec2* posOffsetIn = nullptr, float rotOffsetIn = 0.0, T* ownerIn = nullptr);
	virtual ~Shape(void);

	void setOwner(T*);
	void setPosOffset(glm::vec2*);
	void setAbsPos(glm::vec2*);
	void setRotOffset(float);
	void setAbsRot(float);

	T* getOwner(void);
	glm::vec2 getPosOffset(void);
	glm::vec2 getAbsPos(void);
	float getRotOffset(void);
	float getAbsRot(void);

	//virtual float getArea(void) = 0;
	//virtual std::string getShapeType(void) = 0;

protected:
	glm::vec2* posOffset;
	float rotOffset;
	T* owner;
};

#endif