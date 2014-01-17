#ifndef ITEM_H
#define ITEM_H

#include <string>

class Item
{
public:
	Item(std::string, int, int);

	std::string getName(void);
	int getStackSize(void);
	int getId(void);

private:
	std::string name;
	int stackSize, id;
};

#endif