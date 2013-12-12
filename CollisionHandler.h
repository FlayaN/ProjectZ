#pragma once
#include "Shape.h"

#include "CircleShape.h"

class CollisionHandler
{
public:
	CollisionHandler(void);
	~CollisionHandler(void);

	bool testCollision(Shape*, Shape*);
};

