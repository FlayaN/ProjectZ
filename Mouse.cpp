#include "Mouse.h"

Mouse::Mouse(void)
{
	item = false;
}

void Mouse::setCurrItemStack(std::shared_ptr<ItemStack> currItemStackIn)
{
	if(currItemStackIn != nullptr)
		item = true;
	else
		item = false;
	currItemStack = currItemStackIn;
}

void Mouse::setPosition(glm::vec2 posIn)
{
	pos = posIn;
}

std::shared_ptr<ItemStack> Mouse::getCurrItemStack(void)
{
	return currItemStack;
}

glm::vec2 Mouse::getPosition(void)
{
	return pos;
}

bool Mouse::hasItem(void)
{
	return item;
}