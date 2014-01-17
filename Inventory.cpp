#include "Inventory.h"

Inventory::Inventory(int maxSizeIn) : maxSize(maxSizeIn)
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