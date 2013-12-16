#pragma once

#ifdef __APPLE__
    #include <SDL2/SDL.h>
#else
    #include "SDL.h"
#endif

#include "Coordinate.h"
#include "Shape.h"
#include <vector>

class Entity {
public:
	Entity(void);
	~Entity(void);

	void setPosition(Coordinate*);
	void setVelocity(Coordinate*);

	Coordinate* getPosition(void);
	Coordinate* getVelocity(void);
    
	void updatePosition(void);
	void addShape(Shape*);
	void removeShapes(void);

protected:
	Coordinate* position;
	Coordinate* velocity;
	std::vector<Shape*> shapes; // change to collision boxes based on shapes
};

