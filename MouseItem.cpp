#include "MouseItem.h"

MouseItem::MouseItem(void)
{

}

void MouseItem::setCurrItemStack(std::shared_ptr<ItemStack> currItemStackIn)
{
	currItemStack = currItemStackIn;
}

void MouseItem::setPosition(glm::vec2 posIn)
{
	pos = posIn;
}

std::shared_ptr<ItemStack> MouseItem::getCurrItemStack(void)
{
	return currItemStack;
}

glm::vec2 MouseItem::getPosition(void)
{
	return pos;
}