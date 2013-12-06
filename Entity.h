#pragma once

#ifdef __APPLE__
    #include <SDL2/SDL.h>
#else
    #include "SDL.h"
#endif

#include "Coordinate.h"

class Entity {
public:
	Entity(void);
	~Entity(void);

	Coordinate* getPosition();
	Coordinate* getVelocity();

	void setPosition(float, float, float);
	void setPosition(Coordinate*);



protected:
	Coordinate* position;
	Coordinate* velocity;
};

