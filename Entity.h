#pragma once

#ifdef __APPLE__
    #include <SDL2/SDL.h>
#else
    #include "SDL.h"
#endif

#include <vector>

#include "Vec2.h"
#include "Shape.h"

#ifndef ENTITY_H
#define ENTITY_H

class Entity {
public:
	Entity(void);
	~Entity(void);

	void setPosition(Vec2*);
	void setVelocity(Vec2*);

	Vec2* getPosition(void);
	Vec2* getVelocity(void);
    
	void updatePosition(void);
	void addShape(Shape*);
	void removeShapes(void);

protected:
	Vec2* position;
	Vec2* velocity;
	std::vector<Shape*> shapes; // change to collision boxes based on shapes
};

#endif