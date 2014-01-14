#ifndef ENTITY_H
#define ENTITY_H

#ifdef __APPLE__
    #include <SDL2/SDL.h>
#else
    #include "SDL.h"
#endif

#include <vector>

#include "lib/glm/vec2.hpp"

#include "Shape.h"

class Entity
{
public:
	Entity(void);
	virtual ~Entity(void);

	void setPosition(glm::vec2);
	void setPosition(float x, float y);
	void setRotation(float);

	glm::vec2 getPosition(void);
	float getRotation(void);
    std::vector<Shape*> getShapes(void);
	std::vector<Entity*> getChildren(void);

	void addShape(Shape*);
	void addChild(Entity*);
	
	void removeShapes(void);
	void removeChildren(void);

	void removeShapeAt(int);
	void removeChildAt(int);
	
	void insertShapeAt(int, Shape*);
	void insertChildAt(int, Entity*);

	void releaseChildren(void);

protected:
	glm::vec2 position;
	float rotation;
	std::vector<Shape*> shapes; // shapes with entity as owner
	std::vector<Entity*> children;
};

#endif