#pragma once

#ifdef __APPLE__
    #include <SDL2/SDL.h>
#else
    #include "SDL.h"
#endif

#include "Vec3.h"
#include "Shape.h"
#include <vector>

class Entity {
public:
	Entity(void);
	~Entity(void);

	void setPosition(Vec3*);
	void setVelocity(Vec3*);

	Vec3* getPosition(void);
	Vec3* getVelocity(void);
    
	void updatePosition(void);
	void addShape(Shape*);
	void removeShapes(void);

protected:
	Vec3* position;
	Vec3* velocity;
	std::vector<Shape*> shapes; // change to collision boxes based on shapes
};

