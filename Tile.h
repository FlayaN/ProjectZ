#pragma once

#include <iostream>

#include "Vec3.h"
#include "Shape.h"
#include "Utility.h"
#include "Graphics.h"

#ifndef TILE_H
#define TILE_H

class Tile
{
public:
	//Tile(Vec3*, Shape*, Shape*, Shape*, Shape*);
	Tile(std::string s, Vec2* coord);
	~Tile(void);

	SDL_Texture* getTexture(void);
	SDL_Rect* getBB(void);
	Vec2* getCoord(void);

private:
	//Vec3* position;
	
	Vec2* coord;

	/*Shape* northArea;
	Shape* southArea;
	Shape* westArea;
	Shape* eastArea;*/

	//Shape* bb;
    
	SDL_Rect* bb;

    SDL_Texture* tex;
};

#endif

