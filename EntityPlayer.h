#pragma once

#ifndef ENTITYPLAYER_H
#define ENTITYPLAYER_H

#include <iostream>

#include "RectangleShape.h"
#include "Entity.h"
#include "TextureManager.h"
#include "lib/glm/vec2.hpp"

class EntityPlayer : public Entity {
public:
	EntityPlayer(glm::vec2*, glm::vec2*, std::string, float, glm::vec2*, glm::vec2*, std::string);
	~EntityPlayer(void);
	void keyDown(SDL_Event*);
	void update();

	glm::vec2 getCenterPosition(void);

	void setId(int);
	int getId(void);

	bool isReady(void);

	RectangleShape<Entity>* getModel(void);
	RectangleShape<Entity>* getBB(void);
private:
	int id;
	bool ready;
	float speed;
	RectangleShape<Entity>* model;
	RectangleShape<Entity>* bb;
};

#endif