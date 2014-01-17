#ifndef GROUNDITEM_H
#define GROUNDITEM_H

#include "lib/glm/vec2.hpp"

#include "Item.h"

class GroundItem : public Item
{
public:
	GroundItem(glm::vec2, std::string, int, int);
	glm::vec2 getPosition(void);
private:
	glm::vec2 pos;
};
#endif