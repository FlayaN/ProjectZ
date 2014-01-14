#include "Item.h"

Item::Item(glm::vec2 positionIn, std::string nameIn) : position(positionIn), name(nameIn)
{

}

std::string Item::getName(void)
{
	return name;
}

glm::vec2 Item::getPosition(void)
{
	return position;
}