#include "Item.h"

Item::Item(std::string nameIn, int stackSizeIn, int idIn) : name(nameIn), stackSize(stackSizeIn), id(idIn)
{

}

std::string Item::getName(void)
{
	return name;
}

int Item::getStackSize(void)
{
	return stackSize;
}

int Item::getId(void)
{
	return id;
}