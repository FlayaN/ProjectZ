#include "HeldItem.h"

HeldItem::HeldItem(std::shared_ptr<ItemStack> currItemIn) : currItem(currItemIn)
{

}
void HeldItem::setPosition(glm::vec2 posIn)
{
	pos = posIn;
}

glm::vec2 HeldItem::getPosition(void)
{
	return pos;
}

std::shared_ptr<ItemStack> HeldItem::getCurrItem(void)
{
	return currItem;
}