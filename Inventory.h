#ifndef INVENTORY_H
#define INVENTORY_H

#include <memory>
#include <iostream>

#include "lib/glm/vec2.hpp"

#include "ItemStack.h"
#include "MouseItem.h"

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

	std::shared_ptr<MouseItem> pickupItem(glm::ivec2);
	bool placeItem(glm::ivec2, std::shared_ptr<MouseItem>);
	void pickupOneItem(std::shared_ptr<MouseItem>, glm::ivec2);

private:
	std::vector<std::shared_ptr<ItemStack> > inv;
	int maxSize;
	glm::ivec2 pos;
};

#endif