#pragma once

#include <iostream>

#include "Graphics.h"
#include "entity.h"

#ifndef ENTITYPLAYER_H
#define ENTITYPLAYER_H

class EntityPlayer : public Entity {
public:
	EntityPlayer(void);
	~EntityPlayer(void);
	void keyDown(SDL_Event*);
	void update();

	SDL_Texture* getTexture(void);
	SDL_Texture* getCollisionTexture(void);
	SDL_Rect* getSize(void);
	SDL_Rect* getBB(void);

	Vec2 getCenterPosition(void);
private:
	SDL_Texture* tex;
	SDL_Texture* collisionTex;
	SDL_Rect* size;
	//Shape* bb;

	SDL_Rect* bb;
};

#endif