#ifndef ITEM_H
#define ITEM_H

#include <string>

#include "lib/glm/vec2.hpp"

class Item
{
public:
	Item(glm::vec2, std::string);

	std::string getName(void);
	glm::vec2 getPosition(void);
private:
	std::string name;
	glm::vec2 position;
};

#endif