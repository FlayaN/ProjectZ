#pragma once

#ifndef CollisionHandler_H
#define CollisionHandler_H

#ifdef __APPLE__
	#include <SDL2/SDL.h>
#else
	#include "SDL.h"
#endif

#include "Shape.h"
#include "CircleShape.h"

namespace CollisionHandler
{
	bool testCollision(Shape*, Shape*);
	bool intersects(SDL_Rect* r1, SDL_Rect* r2);
}

#endif