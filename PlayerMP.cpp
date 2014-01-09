#include "PlayerMP.h"

PlayerMP::PlayerMP(int idIn) : id(idIn), Entity()
{
	size = glm::vec2(80, 160);
}

glm::vec2 PlayerMP::getSize(void)
{
	return size;
}

int PlayerMP::getId(void)
{
	return id;
}