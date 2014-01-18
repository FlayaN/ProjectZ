#ifndef ITEMSTACK_H
#define ITEMSTACK_H

#include <vector>
#include <memory>
#include <algorithm>

#include "Item.h"

class ItemStack
{
public:
	ItemStack(int);
	bool addItem(std::shared_ptr<Item>);
	std::shared_ptr<ItemStack> addItemStack(std::shared_ptr<ItemStack>);
	int getCurrSize(void);
	std::shared_ptr<Item> getItem(void);
	int getMaxSize(void);
private:
	std::vector<std::shared_ptr<Item> > items;
	int maxSize;
	int curIndex;
};

#endif