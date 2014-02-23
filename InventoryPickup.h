#ifndef INVENTORYPICKUP_H
#define INVENTORYPICKUP_H

#include "Inventory.h"
#include "GroundItemStack.h"

class InventoryPickup : public Inventory
{
public:
	InventoryPickup(std::shared_ptr<TypeInventory>);

	void addItemStack(std::shared_ptr<GroundItemStack>, std::shared_ptr<Item>);
	std::vector<std::shared_ptr<GroundItemStack> > getGroundItems(void);
	void clearInv(void);
	void increaseRowCount(void);
private:
	std::vector<std::shared_ptr<GroundItemStack> > groundItems;
	//std::vector<std::vector<int> > invItemIds;
	int groundItemsIndex;
};

#endif