#ifndef ITEMSTACK_H
#define ITEMSTACK_H

#include <vector>
#include <memory>
#include <algorithm>
#include <iostream>

#include "Item.h"

class ItemStack
{
public:
	ItemStack(int);
	void setItem(std::shared_ptr<Item>);
	std::shared_ptr<ItemStack> addItemStack(std::shared_ptr<ItemStack>);
	int getCurrSize(void);
	std::shared_ptr<Item> getItem(void);
	int getMaxSize(void);
	void decreaseStack(void);
	bool increaseStack(void);
private:
	std::vector<std::shared_ptr<Item> > items;
	std::shared_ptr<Item> item;
	int maxSize;
	int curIndex;
};

#endif