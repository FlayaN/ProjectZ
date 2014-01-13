#ifndef ENTITYPLAYER_H
#define ENTITYPLAYER_H

#include <iostream>

#include "lib/glm/vec2.hpp"

#include "RectangleShape.h"
#include "MovingEntity.h"
#include "TypePlayer.h"

class EntityPlayer : public MovingEntity
{
public:
	EntityPlayer(TypePlayer);
	~EntityPlayer(void);
	void update(float, const Uint8*);

	glm::vec2 getCenterPosition(void);

	void setId(int);
	int getId(void);
	bool isOnline(void);

	glm::vec2 getSize(void);
	RectangleShape* getBB(void);
	std::string getTexture(void);
	void setFriction(float);
private:
	int id;
	bool online;
	float maxSpeed;
	float acceleration;
	float friction;
	std::string texture;

	glm::vec2 size;
	RectangleShape* bb;
};

#endif