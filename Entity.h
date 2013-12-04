#pragma once

#ifdef __APPLE__
    #include <SDL2/SDL.h>
#else
    #include "SDL.h"
#endif

#include "Position.h"

class Entity {
public:
	Entity(void);
	~Entity(void);

	Position* getPosition();
	Position* getVelocity();

protected:
	Position* position;
	Position* velocity;
};

