#ifndef TILE_H
#define TILE_H

#ifdef __APPLE__
    #include <SDL2/SDL.h>
#else

#endif

#include <iostream>

#include "lib/glm/vec2.hpp"
#include "lib/glm/vec3.hpp"

#include "Shape.h"
#include "Utility.h"
#include "RectangleShape.h"

class Tile
{
public:
	Tile(int, float, glm::ivec2);
	~Tile(void);

	RectangleShape* getBB(void);
	glm::ivec2 getPosition(void);
    glm::vec3* getColorMod(void);
	glm::ivec2 getSize(void);
	int getTextureId(void);
	float getFriction(void);
private:
	glm::ivec2 position;

	RectangleShape* bb;

	glm::ivec2 size;

	int textureId;
	float friction;
};

#endif

