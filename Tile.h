#pragma once

#include <iostream>

//#include "glmVec2Incl.h"
#include "lib/glm/vec2.hpp"
#include "lib/glm/vec3.hpp"
#include "Shape.h"
#include "Utility.h"
#include "TextureManager.h"

#ifndef TILE_H
#define TILE_H

class Tile
{
public:
	//Tile(glm::vec3*, Shape*, Shape*, Shape*, Shape*);
	Tile(std::string, glm::vec2*, glm::vec3*);
	~Tile(void);

	SDL_Texture* getTexture(void);
	SDL_Rect* getBB(void);
	glm::vec2* getPosition(void);
    glm::vec3* getColorMod(void);

private:
	//glm::vec3* position;
	
	glm::vec2* position;

	//Shape* bb;
    
	SDL_Rect* bb;

    SDL_Texture* tex;
    
    glm::vec3* colorMod;
};

#endif

