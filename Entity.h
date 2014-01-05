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
	void setRotation(float);

	Vec2* getPosition(void);
	Vec2* getVelocity(void);
	float getRotation(void);
    std::vector<Shape<Entity>*> getShapes(void);
	std::vector<Entity*> getChildren(void);

	void updatePosition(void);

	void addShape(Shape<Entity>*);
	void addChild(Entity*);
	
	void removeShapes(void);
	void removeChildren(void);

	void removeShapeAt(int);
	void removeChildAt(int);
	
	void insertShapeAt(int, Shape<Entity>*);
	void insertChildAt(int, Entity*);

	void releaseChildren(void);

protected:
	Vec2* position;
	Vec2* velocity;
	float rotation;
	std::vector<Shape<Entity>*> shapes; // shapes with entity as owner
	std::vector<Entity*> children;
};

#endif