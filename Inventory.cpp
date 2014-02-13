#include "Inventory.h"

Inventory::Inventory(int maxRowsIn, int maxColumnsIn, glm::ivec2 posIn) : maxRows(maxRowsIn), maxColumns(maxColumnsIn), pos(posIn)
{
	for(int i = 0; i < maxRowsIn; i++)
		for(int j = 0; j < maxColumns; j++)
			inv.push_back(nullptr);
	currHover = -1;
	maxSize = maxRows*maxColumns;
}

bool Inventory::addItemStack(std::shared_ptr<ItemStack> item)
{
	bool tmp = false;
	for(int i = 0; i < item->getCurrSize(); i++)
	{
		tmp = addItem(item->getItem());
	}
	return tmp;
}

bool Inventory::addItem(std::shared_ptr<Item> item)
{
	if(getCurrSize() < maxSize)
	{
		for(int i = 0; i < inv.size(); i++)
		{
			if(inv.at(i) != nullptr)
			{
				if(inv.at(i)->getItem()->getId() == item->getId())
				{
					bool tmp = inv.at(i)->increaseStack();
					if(tmp)
						return tmp;
				}
			}
		}
		
		for(int i = 0; i < inv.size(); i++)
		{
			if(inv.at(i) == nullptr)
			{
				std::shared_ptr<ItemStack> tmpItemStack = std::make_shared<ItemStack>(item);
				inv.at(i) = tmpItemStack;
				return inv.at(i)->increaseStack();
			}
		}
	}
	return false;
}

int Inventory::getCurrSize(void)
{
	return (maxSize - std::count(inv.begin(), inv.end(), nullptr));
}

std::vector<std::shared_ptr<ItemStack> > Inventory::getItems(void)
{
	return inv;
}

glm::ivec2 Inventory::getPosition(void)
{
	return pos;
}

std::shared_ptr<Mouse> Inventory::pickupItem(glm::ivec2 mousePos)
{
	std::shared_ptr<Mouse> tmpMouse = std::make_shared<Mouse>();
	int index = mousePosToIndex(mousePos);

	if(index != -1)
	{
		if(inv.at(index) != nullptr)
		{
			tmpMouse->setCurrItemStack(inv.at(index));
			tmpMouse->setPosition((glm::vec2)mousePos);
			inv.at(index) = nullptr;
		}
	}
	else
		tmpMouse->setCurrItemStack(nullptr);
	return tmpMouse;
}

void Inventory::pickupOneItem(std::shared_ptr<Mouse> mouse, glm::ivec2 mousePos)
{
	int index = mousePosToIndex(mousePos);

	if(index != -1)
	{
		if(inv.at(index) != nullptr)
		{
			if(mouse->getCurrItemStack() == nullptr)
			{
				std::shared_ptr<ItemStack> tmpItemStack = std::make_shared<ItemStack>(*inv.at(index));
				tmpItemStack->increaseStack();
				mouse->setCurrItemStack(tmpItemStack);
				mouse->setPosition((glm::vec2)mousePos);
				inv.at(index)->decreaseStack();
				if(inv.at(index)->getCurrSize() < 1)
					inv.at(index) = nullptr;
					
			}
			else
			{
				if(mouse->getCurrItemStack()->getItem()->getId() == inv.at(index)->getItem()->getId())
				{

					if(mouse->getCurrItemStack()->increaseStack())
					{
						inv.at(index)->decreaseStack();
						if(inv.at(index)->getCurrSize() < 1)
							inv.at(index) = nullptr;
					}
				}
			}
		}
	}
}

bool Inventory::placeItem(glm::ivec2 mousePos, std::shared_ptr<Mouse> mouse)
{
	int index = mousePosToIndex(mousePos);

	if(index != -1)
	{
		if(inv.at(index) == nullptr)
		{
			inv.at(index) = mouse->getCurrItemStack();
			mouse->setCurrItemStack(nullptr);
		}
		else
		{
			if(inv.at(index)->getItem()->getId() == mouse->getCurrItemStack()->getItem()->getId())
			{
				mouse->setCurrItemStack(inv.at(index)->addItemStack(mouse->getCurrItemStack()));
			}
			else
			{
				std::shared_ptr<ItemStack> tmp = inv.at(index);
				inv.at(index) = mouse->getCurrItemStack();
				mouse->setCurrItemStack(tmp);
			}
		}
		return true;
	}
	return false;
}

int Inventory::mousePosToIndex(glm::ivec2 mouse)
{
	glm::ivec2 tmpPos = mouse - pos;

	tmpPos.x = tmpPos.x >= 0 ? (tmpPos.x/34) : (tmpPos.x/34)-1;
	tmpPos.y = tmpPos.y >= 0 ? (tmpPos.y/34) : (tmpPos.y/34)-1;

	if(tmpPos.x >= 0 && tmpPos.x < maxColumns && tmpPos.y >= 0 && tmpPos.y < maxRows)
	{
		int tmpIndex = tmpPos.x + (tmpPos.y*maxColumns);
		currHover = tmpIndex;
		return tmpIndex;
	}
	currHover = -1;
	return -1;
}

int Inventory::getCurrHover(void)
{
	return currHover;
}

int Inventory::getMaxRows(void)
{
	return maxRows;
}

int Inventory::getMaxColumns(void)
{
	return maxColumns;
}

int Inventory::getMaxSize(void)
{
	return maxSize;
}