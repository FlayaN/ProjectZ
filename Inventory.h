#ifndef INVENTORY_H
#define INVENTORY_H

#include <memory>
#include <iostream>

#include "lib/glm/vec2.hpp"

#include "ItemStack.h"
#include "Mouse.h"

class Inventory
{
public:
	Inventory(int, glm::ivec2);

	bool addItemStack(std::shared_ptr<ItemStack>);
	bool addItem(std::shared_ptr<Item>);
	int getCurrSize(void);
	std::vector<std::shared_ptr<ItemStack> > getItems(void);
	glm::ivec2 getPosition(void);

	int mousePosToIndex(glm::ivec2 mouse);

	std::shared_ptr<Mouse> pickupItem(glm::ivec2);
	bool placeItem(glm::ivec2, std::shared_ptr<Mouse>);
	void pickupOneItem(std::shared_ptr<Mouse>, glm::ivec2);
	int getCurrHover(void);
private:
	std::vector<std::shared_ptr<ItemStack> > inv;
	int maxSize;
	glm::ivec2 pos;
	int currHover;
};

#endif