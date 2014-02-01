#include "GroundItem.h"

GroundItem::GroundItem(int idIn, glm::vec2 posIn) : pos(posIn), id(idIn)
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