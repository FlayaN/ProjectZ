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

bool GroundItemStack::operator==(const GroundItemStack &other) const
{
	return pos == other.pos && id == other.id && amount == other.amount;
}