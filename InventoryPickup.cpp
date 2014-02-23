#include "InventoryPickup.h"

InventoryPickup::InventoryPickup(std::shared_ptr<TypeInventory> inventoryType) : Inventory(inventoryType)
{
	clearInv();
}

void InventoryPickup::clearInv(void)
{
	maxRows = 0;
	maxColumns = 1;
	maxSize = 0;
	groundItemsIndex = 0;

	groundItems.clear();
	inv.clear();

	//groundItems.push_back(nullptr);
	//inv.push_back(nullptr);
}

void InventoryPickup::increaseRowCount(void)
{
	maxRows++;
	maxSize = maxRows * maxColumns;

	groundItems.push_back(nullptr);
	inv.push_back(nullptr);
}

void InventoryPickup::addItemStack(std::shared_ptr<GroundItemStack> groundItem, std::shared_ptr<Item> item)
{
	increaseRowCount();
	groundItems[groundItemsIndex] = groundItem;

	for(int i = 0; i < groundItem->getAmount(); i++)
	{
		addItem(item);
	}

	groundItemsIndex++;
	
	//std::cout << "groundItems count of groundItem: " << std::count(groundItems.begin(), groundItems.end(), groundItem) << std::endl;
	//bool itemExists = false;
	/*for(auto tmpGroundItem : groundItems)
	{
		if(tmpGroundItem != nullptr)
			if(groundItem->getId() == tmpGroundItem->getId())
				itemExists = true;
	}

	if(!itemExists)
	{
		increaseRowCount();
		groundItems[groundItemsIndex] = groundItem;

		for(int i = 0; i < groundItem->getAmount(); i++)
		{
			addItem(item);
		}

		groundItemsIndex++;
	}*/
}

std::vector<std::shared_ptr<GroundItemStack> > InventoryPickup::getGroundItems(void)
{
	return groundItems;
}