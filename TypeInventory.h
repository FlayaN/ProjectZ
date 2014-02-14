#ifndef TYPEINVENTORY_H
#define TYPEINVENTORY_H

#include <string>

#include "lib/glm/vec2.hpp"

struct TypeInventory
{
	std::string name;
	glm::vec2 startPos;
	int rowCount;
	int columnCount;
};

#endif