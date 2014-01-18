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

std::shared_ptr<ItemStack> ItemStack::addItemStack(std::shared_ptr<ItemStack> itemStackIn)
{
	std::shared_ptr<ItemStack> tmpItemStack = std::make_shared<ItemStack>(ItemStack(itemStackIn->getMaxSize()));

	int cnt = 0;
	for(int i = 0; i < itemStackIn->getCurrSize(); i++)
	{
		if(!addItem(itemStackIn->getItem()))
		{
			cnt++;
			tmpItemStack->addItem(itemStackIn->getItem());
		}
	}

	if(cnt == 0)
		return nullptr;
	else
		return tmpItemStack;
}

int ItemStack::getCurrSize(void)
{
	return (maxSize - std::count(items.begin(), items.end(), nullptr));
}

std::shared_ptr<Item> ItemStack::getItem(void)
{
	return items.at(0);
}

int ItemStack::getMaxSize(void)
{
	return maxSize;
}