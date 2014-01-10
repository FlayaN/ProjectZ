#pragma once

#ifndef ENTITYPLAYER_H
#define ENTITYPLAYER_H

#include <iostream>

#include "lib/glm/vec2.hpp"

#include "RectangleShape.h"
#include "Entity.h"
#include "TextureManager.h"

class EntityPlayer : public Entity {
public:
	EntityPlayer(glm::vec2*, glm::vec2, std::string, glm::vec2*, glm::vec2*, std::string, float, float, float);
	~EntityPlayer(void);
	void update(float, const Uint8*);

	glm::vec2 getCenterPosition(void);

	void setId(int);
	int getId(void);

	bool isOnline(void);

	glm::vec2 getSize(void);
	RectangleShape<Entity>* getBB(void);
private:
	int id;
	bool online;
	float maxSpeed;
	float acceleration;
	float friction;

	glm::vec2 size;
	RectangleShape<Entity>* bb;
};

#endif