#include "GroundItemStack.h"

GroundItemStack::GroundItemStack(int idIn, glm::vec2 posIn, int amountIn) : pos(posIn), id(idIn), amount(amountIn)
{

}

glm::vec2 GroundItemStack::getPosition(void)
{
	return pos;
}

int GroundItemStack::getId(void)
{
	return id;
}

int GroundItemStack::getAmount()
{
	return amount;
}