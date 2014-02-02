#include "GroundItem.h"

GroundItem::GroundItem(int idIn, glm::vec2 posIn, int amountIn) : pos(posIn), id(idIn), amount(amountIn)
{

}

glm::vec2 GroundItem::getPosition(void)
{
	return pos;
}

int GroundItem::getId(void)
{
	return id;
}

int GroundItem::getAmount()
{
	return amount;
}