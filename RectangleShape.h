#ifndef RECTANGLESHAPE_H
#define RECTANGLESHAPE_H

#include <vector>

#include "Shape.h"

class RectangleShape : protected Shape
{
public:
	RectangleShape(glm::vec2* posOffsetIn = nullptr, float rotOffsetIn = 0.0f, glm::vec2* sizeIn = new glm::vec2());
	virtual ~RectangleShape(void);

	void setWidth(float);
	void setHeight(float);

	float getWidth(void);
	float getHeight(void);
	float getArea(void);
	std::string getShapeType(void);

private:

	glm::vec2* size;
};

#endif