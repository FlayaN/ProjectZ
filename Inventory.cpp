#include "Inventory.h"

Inventory::Inventory(int maxSizeIn, glm::ivec2 posIn) : maxSize(maxSizeIn), pos(posIn)
{
	for(int i = 0; i < maxSize; i++)
		inv.push_back(nullptr);
}

bool Inventory::addItemStack(std::shared_ptr<ItemStack> itemStack)
{
	if(getCurrSize() < maxSize)
	{
		inv.push_back(itemStack);
		return true;
	}
	return false;
}

bool Inventory::addItem(int index, std::shared_ptr<Item> item)
{
	if(getCurrSize() < maxSize)
	{
		if(inv.at(index) != nullptr)
		{
			return inv.at(index)->addItem(item);
		}
		else
		{
			inv.at(index) = std::make_shared<ItemStack>(ItemStack(item->getStackSize()));
			return inv.at(index)->addItem(item);
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

std::shared_ptr<ItemStack> Inventory::pickupItem(glm::ivec2 mouse)
{
	int index = mousePosToIndex(mouse);

	if(index != -1)
	{
		std::shared_ptr<ItemStack> tmpItem = inv.at(index);
		inv.at(index) = nullptr;
		return tmpItem;
	}

	return nullptr;
}

void Inventory::placeItem(glm::ivec2 mouse, std::shared_ptr<ItemStack> item)
{
	int index = mousePosToIndex(mouse);

	if(index != -1)
	{
		inv.at(index) = item;
	}
}

int Inventory::mousePosToIndex(glm::ivec2 mouse)
{
	glm::ivec2 tmpPos = mouse - pos;

	tmpPos.x = tmpPos.x >= 0 ? (tmpPos.x/34) : (tmpPos.x/34)-1;
	tmpPos.y = tmpPos.y >= 0 ? (tmpPos.y/34) : (tmpPos.y/34)-1;

	if(tmpPos.x >= 0 && tmpPos.x < 9 && tmpPos.y >= 0 && tmpPos.y < 3)
	{
		return tmpPos.x + (tmpPos.y*9);
	}

	return -1;
}
