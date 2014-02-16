#ifndef ENTITYPLAYER_H
#define ENTITYPLAYER_H

#include <iostream>
#include <memory>

#include "lib/glm/vec2.hpp"

#include "RectangleShape.h"
#include "MovingEntity.h"
#include "TypePlayer.h"
#include "TypeInventory.h"
#include "Inventory.h"
#include "Settings.h"
#include "Mouse.h"
#include "GroundItemStack.h"

class EntityPlayer : public MovingEntity
{
public:
	EntityPlayer(TypePlayer);
	~EntityPlayer(void);

	void update(float, const Uint8*);
	void updateNoKey(float);

	glm::vec2 getCenterPosition(void);

	void setId(int);
	int getId(void);
	bool isOnline(void);

	glm::vec2 getSize(void);
	RectangleShape* getBB(void);
	std::string getTexture(void);
	void setFriction(float);

	std::shared_ptr<Inventory> getInventory(void);

	bool hasInventoryOpen(void);

	void setInventory(std::shared_ptr<Inventory>);
	void toggleInventory(void);
private:
	int id;
	bool online;
	bool inventoryOpen;
	float maxSpeed;
	float acceleration;
	float friction;
	std::string texture;

	

	glm::vec2 size;
	RectangleShape* bb;
	std::shared_ptr<Inventory> inventory;
};

#endif