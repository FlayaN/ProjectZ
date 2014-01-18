#ifndef HELDITEM_H
#define HELDITEM_H

#include "lib/glm/vec2.hpp"

#include "ItemStack.h"

class MouseItem
{
public:
	MouseItem(void);
	
	void setCurrItem(std::shared_ptr<ItemStack>);
	void setPosition(glm::vec2);
	
	std::shared_ptr<ItemStack> getCurrItem(void);
	glm::vec2 getPosition(void);
private:
	std::shared_ptr<ItemStack> currItem;
	glm::vec2 pos;
};

#endif