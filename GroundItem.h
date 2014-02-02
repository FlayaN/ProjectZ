#ifndef GROUNDITEM_H
#define GROUNDITEM_H

#include "lib/glm/vec2.hpp"

class GroundItem
{
public:
	GroundItem(int, glm::vec2, int);
	glm::vec2 getPosition(void);
	int getId();
	int getAmount();
private:
	int id;
	int amount;
	glm::vec2 pos;
};
#endif