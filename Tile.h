#pragma once

#include <iostream>

#include "Vec3.h"
#include "Shape.h"
#include "Utility.h"
#include "TextureManager.h"

#ifndef TILE_H
#define TILE_H

class Tile
{
public:
	//Tile(Vec3*, Shape*, Shape*, Shape*, Shape*);
	Tile(std::string, Vec2*, Vec3*);
	~Tile(void);

	SDL_Texture* getTexture(void);
	SDL_Rect* getBB(void);
	Vec2* getPosition(void);
    Vec3* getColorMod(void);

private:
	//Vec3* position;
	
	Vec2* position;

	//Shape* bb;
    
	SDL_Rect* bb;

    SDL_Texture* tex;
    
    Vec3* colorMod;
};

#endif

