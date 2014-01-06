#pragma once

#include <iostream>

#include "entity.h"
#include "TextureManager.h"

#ifndef ENTITYPLAYER_H
#define ENTITYPLAYER_H

class EntityPlayer : public Entity {
public:
	EntityPlayer(glm::vec2*, glm::vec2*, std::string, float, glm::vec2*, glm::vec2*, std::string);
	~EntityPlayer(void);
	void keyDown(SDL_Event*);
	void update();

	SDL_Texture* getTexture(void);
	SDL_Texture* getCollisionTexture(void);
	SDL_Rect* getSize(void);
	SDL_Rect* getBB(void);

	glm::vec2 getCenterPosition(void);

	void setId(int);
	int getId(void);

	bool isReady(void);
private:
	int id;
	bool ready;
	SDL_Texture* tex;
	SDL_Texture* collisionTex;
	SDL_Rect* size;
	//Shape* bb;

	SDL_Rect* bb;
	float speed;
};

#endif