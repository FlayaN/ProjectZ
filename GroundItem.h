#ifndef GROUNDITEM_H
#define GROUNDITEM_H

#include "lib/glm/vec2.hpp"

class GroundItem
{
public:
	GroundItem(int, glm::vec2);
	glm::vec2 getPosition(void);
	int getId();
private:
	int id;
	glm::vec2 pos;
};
#endif