#include "ItemStack.h"

ItemStack::ItemStack(std::shared_ptr<Item> itemIn, int maxSizeIn) : item(itemIn), maxSize(maxSizeIn), currSize(0)
{

}

ItemStack::ItemStack(const ItemStack& other)
{
	item = other.item;
	maxSize = other.maxSize;
	currSize = 0;
}

void ItemStack::setItem(std::shared_ptr<Item> itemIn)
{
	item = itemIn;
}

std::shared_ptr<ItemStack> ItemStack::addItemStack(std::shared_ptr<ItemStack> itemStackIn)
{
	std::shared_ptr<ItemStack> tmpItemStack = std::make_shared<ItemStack>(*itemStackIn);
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
		currSize--;
	}
}

bool ItemStack::increaseStack(void)
{
	if(getCurrSize() < maxSize)
	{
		currSize++;
		return true;
	}
	return false;
}

int ItemStack::getCurrSize(void)
{
	return currSize;
}

std::shared_ptr<Item> ItemStack::getItem(void)
{
	return item;
}

int ItemStack::getMaxSize(void)
{
	return maxSize;
}