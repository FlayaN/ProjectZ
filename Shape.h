#pragma once

#include <string>
#include <math.h>

#include "TextureManager.h"
#include "lib/glm/vec2.hpp"
#include <SDL.h>

#ifndef SHAPE_H
#define SHAPE_H

class Shape
{
public:
	Shape(glm::vec2* posOffsetIn = nullptr, float rotOffsetIn = 0.0);
	virtual ~Shape(void);

	void setPosOffset(glm::vec2*);
	void setRotOffset(float);

	glm::vec2 getPosOffset(void);
	float getRotOffset(void);

	//virtual float getArea(void) = 0;
	//virtual std::string getShapeType(void) = 0;

protected:
	glm::vec2* posOffset;
	float rotOffset;
};

#endif