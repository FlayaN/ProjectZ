#pragma once

#include "Entity.h"
#include "TextureManager.h"

#ifndef PLAYERMP_H
#define PLAYERMP_H

class PlayerMP : public Entity
{
public:
	PlayerMP(int);
	SDL_Rect* getSize(void);

	int getId(void);
private:
	int id;
	SDL_Rect* size;
};

#endif