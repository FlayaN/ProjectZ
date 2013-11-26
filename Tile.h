#pragma once

#ifdef __APPLE__
    #include <SDL2/SDL.h>
#else
    #include "SDL.h"
#endif

#include "Position.h"
#include "Area.h"
#include <iostream>
#include <SDL2_image/SDL_image.h>

class Tile
{
public:
	Tile(Position*, Area*, Area*, Area*, Area*);
    Tile(SDL_Renderer*);
	~Tile(void);
    
    SDL_Texture* getTexture();

private:
	Position* position;

	Area* northArea;
	Area* southArea;
	Area* westArea;
	Area* eastArea;
    
    SDL_Texture* tex = nullptr;
    
    SDL_Surface* surface;
    
    SDL_Rect r;
    
};

