#ifndef GROUNDITEMSTACK_H
#define GROUNDITEMSTACK_H

#include "lib/glm/vec2.hpp"

class GroundItemStack
{
public:
	GroundItemStack(int, glm::vec2, int);
	glm::vec2 getPosition(void);
	int getId();
	int getAmount();

	bool operator==(const GroundItemStack &other) const;
private:
	int id;
	int amount;
	glm::vec2 pos;
};

#endif