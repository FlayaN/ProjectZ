#ifndef MOUSEITEM_H
#define MOUSEITEM_H

#include "lib/glm/vec2.hpp"

#include "ItemStack.h"

class Mouse
{
public:
	Mouse(void);
	
	void setCurrItemStack(std::shared_ptr<ItemStack>);
	void setPosition(glm::vec2);
	
	std::shared_ptr<ItemStack> getCurrItemStack(void);
	glm::vec2 getPosition(void);

	bool hasItem(void);
private:
	bool item;
	std::shared_ptr<ItemStack> currItemStack;
	glm::vec2 pos;
};

#endif