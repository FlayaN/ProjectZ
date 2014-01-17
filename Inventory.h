#ifndef INVENTORY_H
#define INVENTORY_H

#include <memory>

#include "ItemStack.h"

class Inventory
{
public:
	Inventory(int);
	bool addItemStack(std::shared_ptr<ItemStack>);
	bool addItem(int, std::shared_ptr<Item>);
	int getCurrSize(void);
	std::vector<std::shared_ptr<ItemStack> > getItems(void);

private:
	std::vector<std::shared_ptr<ItemStack> > inv;
	int maxSize;
};

#endif