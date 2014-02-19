#include "InventoryPickup.h"

InventoryPickup::InventoryPickup(std::shared_ptr<TypeInventory> inventoryType) : Inventory(inventoryType)
{
	clearInv();
}

void InventoryPickup::clearInv(void)
{
	groundItemsIndex = 0;
	groundItems.clear();
	inv.clear();
	for(int i = 0; i < maxRows; i++)
		for(int j = 0; j < maxColumns; j++)
		{
			groundItems.push_back(nullptr);
			inv.push_back(nullptr);
		}
}

void InventoryPickup::addItemStack(std::shared_ptr<GroundItemStack> groundItem, std::shared_ptr<Item> item)
{
	if(groundItemsIndex >= maxSize) return;

	if(std::count(groundItems.begin(), groundItems.end(), groundItem) == 0)
	{
		groundItems[groundItemsIndex] = groundItem;
		for(int i = 0; i < groundItem->getAmount(); i++)
		{
			addItem(item);
		}
		groundItemsIndex++;
	}
}

std::vector<std::shared_ptr<GroundItemStack> > InventoryPickup::getGroundItems(void)
{
	return groundItems;
}