#include "ItemStack.h"

ItemStack::ItemStack(std::shared_ptr<Item> itemIn) : item(itemIn), currSize(0)
{

}

ItemStack::~ItemStack(void)
{
	item.reset();
}

ItemStack::ItemStack(const ItemStack& other)
{
	item = other.item;
	currSize = 0;
}

std::shared_ptr<ItemStack> ItemStack::addItemStack(std::shared_ptr<ItemStack> itemStackIn)
{
	std::shared_ptr<ItemStack> tmpItemStack = std::make_shared<ItemStack>(*itemStackIn);

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
	if(getCurrSize() < item->getStackSize())
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