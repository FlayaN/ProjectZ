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
	ItemStack(std::shared_ptr<Item>);
	~ItemStack(void);
	ItemStack(const ItemStack&);

	std::shared_ptr<Item> getItem(void);
	int getCurrSize(void);

	std::shared_ptr<ItemStack> addItemStack(std::shared_ptr<ItemStack>);
	void decreaseStack(void);
	bool increaseStack(void);
private:
	std::shared_ptr<Item> item;
	int currSize;
};

#endif