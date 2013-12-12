#pragma once

#ifdef __APPLE__
	#include <SDL2/SDL.h>
	#include <SDL2_image/SDL_image.h>
#else
	#include "SDL.h"
	#include "SDL_image.h"
#endif

#include "Coordinate.h"
#include "Shape.h"
#include <iostream>

class Tile
{
public:
	Tile(Coordinate*, Shape*, Shape*, Shape*, Shape*);
    Tile(SDL_Renderer*, std::string s);
	~Tile(void);
    
    SDL_Texture* getTexture();

private:
	Coordinate* position;

	Shape* northArea;
	Shape* southArea;
	Shape* westArea;
	Shape* eastArea;
    
    SDL_Texture* tex;
};

