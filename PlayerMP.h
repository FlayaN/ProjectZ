#pragma once

#include "Entity.h"
#include "TextureManager.h"
#include "RectangleShape.h"

#ifndef PLAYERMP_H
#define PLAYERMP_H

class PlayerMP : public Entity
{
public:
	PlayerMP(int);
	glm::vec2 getSize(void);

	int getId(void);
private:
	int id;
	glm::vec2 size;
};

#endif