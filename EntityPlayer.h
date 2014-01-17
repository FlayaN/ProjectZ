#ifndef ENTITYPLAYER_H
#define ENTITYPLAYER_H

#include <iostream>
#include <memory>

#include "lib/glm/vec2.hpp"

#include "RectangleShape.h"
#include "MovingEntity.h"
#include "TypePlayer.h"
#include "Inventory.h"

class EntityPlayer : public MovingEntity
{
public:
	EntityPlayer(TypePlayer);
	~EntityPlayer(void);

	void onEvent(SDL_Event*);
	void update(float, const Uint8*);

	glm::vec2 getCenterPosition(void);

	void setId(int);
	int getId(void);
	bool isOnline(void);

	glm::vec2 getSize(void);
	RectangleShape* getBB(void);
	std::string getTexture(void);
	void setFriction(float);

	std::vector<std::shared_ptr<ItemStack> > getItems(void);

	std::shared_ptr<Inventory> getInventory(void);

	bool hasInventoryOpen(void);
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