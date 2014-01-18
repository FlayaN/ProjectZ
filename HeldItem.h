#ifndef HELDITEM_H
#define HELDITEM_H

#include "lib/glm/vec2.hpp"

#include "ItemStack.h"

class HeldItem
{
public:
	HeldItem(std::shared_ptr<ItemStack>);
	void setPosition(glm::vec2);
	glm::vec2 getPosition(void);
	std::shared_ptr<ItemStack> getCurrItem(void);
private:
	std::shared_ptr<ItemStack> currItem;
	glm::vec2 pos;
};

#endif