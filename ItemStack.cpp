#include "ItemStack.h"

ItemStack::ItemStack(int maxSizeIn) : maxSize(maxSizeIn)
{
	for(int i = 0; i < maxSize; i++)
		items.push_back(nullptr);
	curIndex = 0;
}

void ItemStack::setItem(std::shared_ptr<Item> itemIn)
{
	item = itemIn;
}

std::shared_ptr<ItemStack> ItemStack::addItemStack(std::shared_ptr<ItemStack> itemStackIn)
{
	std::shared_ptr<ItemStack> tmpItemStack = std::make_shared<ItemStack>(ItemStack(itemStackIn->getMaxSize()));
	tmpItemStack->setItem(itemStackIn->getItem());

	int cnt = 0;
	for(int i = 0; i < itemStackIn->getCurrSize(); i++)
	{
		if(!increaseStack())
		{
			cnt++;
			tmpItemStack->increaseStack();
		}
	}

	if(cnt == 0)
		return nullptr;
	else
		return tmpItemStack;
}

void ItemStack::decreaseStack(void)
{
	if(getCurrSize() > 0)
	{
		items.at(--curIndex) = nullptr;
	}
}

bool ItemStack::increaseStack(void)
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
	return item;
}

int ItemStack::getMaxSize(void)
{
	return maxSize;
}