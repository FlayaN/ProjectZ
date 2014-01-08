#pragma once

#include <iostream>

//#include "glmVec2Incl.h"
#include "lib/glm/vec2.hpp"
#include "lib/glm/vec3.hpp"
#include "Shape.h"
#include "Utility.h"
#include "TextureManager.h"
#include "RectangleShape.h"

#ifndef TILE_H
#define TILE_H

class Tile
{
public:
	Tile(std::string, glm::vec2*, glm::vec3*);
	~Tile(void);

	RectangleShape<Tile>* getBB(void);
	glm::vec2* getPosition(void);
    glm::vec3* getColorMod(void);

private:
	glm::vec2* position;

	RectangleShape<Tile>* bb;
    
    glm::vec3* colorMod;
};

#endif

