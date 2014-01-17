#include "GroundItem.h"

GroundItem::GroundItem(glm::vec2 posIn, std::string nameIn, int stackSizeIn, int idIn) : Item(nameIn, stackSizeIn, idIn), pos(posIn)
{

}

glm::vec2 GroundItem::getPosition(void)
{
	return pos;
}

