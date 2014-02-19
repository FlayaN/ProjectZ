#ifndef INVENTORY_H
#define INVENTORY_H

#include <memory>
#include <iostream>

#include "lib/glm/vec2.hpp"

#include "ItemStack.h"
#include "Mouse.h"
#include "TypeInventory.h"

class Inventory
{
public:
	Inventory(std::shared_ptr<TypeInventory>);

	bool addItemStack(std::shared_ptr<ItemStack>);
	bool addItem(std::shared_ptr<Item>);

	int mousePosToIndex(glm::ivec2 mouse);

	std::shared_ptr<Mouse> pickupItem(glm::ivec2);
	bool placeItem(glm::ivec2, std::shared_ptr<Mouse>);
	void pickupOneItem(std::shared_ptr<Mouse>, glm::ivec2);
	
	int getCurrHover(void);
	int getMaxRows(void);
	int getMaxColumns(void);
	int getMaxSize(void);
	int getCurrSize(void);
	std::vector<std::shared_ptr<ItemStack> > getItems(void);
	glm::ivec2 getPosition(void);
protected:
	std::vector<std::shared_ptr<ItemStack> > inv;
	int maxRows;
	int maxColumns;
	int maxSize;
	glm::ivec2 pos;
	int currHover;
};

#endif