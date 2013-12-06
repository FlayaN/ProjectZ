#pragma once

#ifdef __APPLE__
	#include <SDL2/SDL.h>
	#include <SDL2_image/SDL_image.h>
#else
	#include "SDL.h"
	#include "SDL_image.h"
#endif

#include "Coordinate.h"
#include "Area.h"
#include <iostream>

class Tile
{
public:
	Tile(Coordinate*, Area*, Area*, Area*, Area*);
    Tile(SDL_Renderer*);
	~Tile(void);
    
    SDL_Texture* getTexture();

private:
	Coordinate* position;

	Area* northArea;
	Area* southArea;
	Area* westArea;
	Area* eastArea;
    
    SDL_Texture* tex;
};

