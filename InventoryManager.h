#ifndef INVENTORYMANAGER_H
#define INVENTORYMANAGER_H

#include <memory>
#include <vector>

#include "SDL.h"

#include "TypeInventory.h"
#include "Inventory.h"
#include "EntityPlayer.h"

class InventoryManager
{
public:
	InventoryManager(std::vector<std::shared_ptr<TypeInventory> >, std::shared_ptr<EntityPlayer>);
	~InventoryManager(void);

	void onEvent(SDL_Event* ev);

	std::shared_ptr<Mouse> getMouse(void);

	std::shared_ptr<GroundItemStack> getDroppedItemStack(void);
	void setDropItem(bool);
	bool getDropItem(void);
	std::vector<std::shared_ptr<Inventory> > getInventories(void);
private:
	std::vector<std::shared_ptr<Inventory> > inventories;

	std::shared_ptr<EntityPlayer> player;
	std::shared_ptr<Mouse> mouse;
	bool dropItem;

	std::shared_ptr<GroundItemStack> droppedItemStack;
};

#endif