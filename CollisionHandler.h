#pragma once

#ifdef __APPLE__
	#include <SDL2/SDL.h>
#else
	#include "SDL.h"
#endif

#include "Shape.h"
#include "CircleShape.h"

#ifndef COLLISIONHANDLER_H
#define COLLISIONHANDLER_H

namespace CollisionHandler
{
	bool testCollision(Shape*, Shape*);
	bool intersects(SDL_Rect* r1, SDL_Rect* r2);
};

#endif