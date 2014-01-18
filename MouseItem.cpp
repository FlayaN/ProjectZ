#include "MouseItem.h"

MouseItem::MouseItem(void)
{

}

void MouseItem::setCurrItem(std::shared_ptr<ItemStack> currItemIn)
{
	currItem = currItemIn;
}

void MouseItem::setPosition(glm::vec2 posIn)
{
	pos = posIn;
}

std::shared_ptr<ItemStack> MouseItem::getCurrItem(void)
{
	return currItem;
}

glm::vec2 MouseItem::getPosition(void)
{
	return pos;
}