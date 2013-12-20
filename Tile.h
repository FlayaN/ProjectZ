#pragma once

#ifdef __APPLE__
	#include <SDL2/SDL.h>
    #include <SDL2_image/SDL_image.h>
#else
	#include "SDL.h"
	#include "SDL_image.h"
#endif

#include <iostream>

#include "Vec3.h"
#include "Shape.h"
#include "Utility.h"
#include "Defines.h"
#include "Vec2.h"
class Tile
{
public:
	Tile(Vec3*, Shape*, Shape*, Shape*, Shape*);
    Tile(SDL_Renderer*, std::string s, Vec2* coord);
	~Tile(void);
    
    SDL_Texture* getTexture(void);
	SDL_Rect* getBB(void);
    Vec2* getVec2(void);

private:
	Vec3* position;
    
    Vec2* coord;

	Shape* northArea;
	Shape* southArea;
	Shape* westArea;
	Shape* eastArea;

	//Shape* bb;
    
	SDL_Rect* bb;

    SDL_Texture* tex;
};

