#include "ItemStack.h"

ItemStack::ItemStack(int maxSizeIn) : maxSize(maxSizeIn)
{
	for(int i = 0; i < maxSize; i++)
		items.push_back(nullptr);
	curIndex = 0;
}

bool ItemStack::addItem(std::shared_ptr<Item> item)
{
	if(getCurrSize() < maxSize)
	{
		items.at(curIndex++) = item;
		return true;
	}
	return false;
}
int ItemStack::getCurrSize(void)
{
	return (maxSize - std::count(items.begin(), items.end(), nullptr));
}

std::shared_ptr<Item> ItemStack::getItem(void)
{
	return items.at(0);
}