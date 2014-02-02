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
	ItemStack(std::shared_ptr<Item>, int);
	ItemStack(const ItemStack&);

	void setItem(std::shared_ptr<Item>);
	
	std::shared_ptr<Item> getItem(void);
	int getCurrSize(void);
	int getMaxSize(void);

	std::shared_ptr<ItemStack> addItemStack(std::shared_ptr<ItemStack>);
	void decreaseStack(void);
	bool increaseStack(void);
private:
	std::shared_ptr<Item> item;
	int maxSize;
	int currSize;
};

#endif