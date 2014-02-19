#ifndef INVENTORYMANAGER_H
#define INVENTORYMANAGER_H

#include <memory>
#include <vector>
#include <unordered_map>

#include "SDL.h"

#include "TypeInventory.h"
#include "InventoryPickup.h"
#include "EntityPlayer.h"
#include "Defines.h"
#include "ChunkUtility.h"
#include "Network.h"

class InventoryManager
{
public:
	InventoryManager(std::vector<std::shared_ptr<TypeInventory> >, std::shared_ptr<EntityPlayer>);
	~InventoryManager(void);

	void onEvent(SDL_Event* ev, std::HashMap<glm::ivec2, std::shared_ptr<Chunk> >&, std::shared_ptr<Network>);

	std::shared_ptr<Mouse> getMouse(void);

	//std::shared_ptr<GroundItemStack> getDroppedItemStack(void);
	//void setDropItem(bool);
	//bool getDropItem(void);
	std::vector<std::shared_ptr<Inventory> > getInventories(void);
	std::shared_ptr<InventoryPickup> getPickupInventory(void);
private:
	std::vector<std::shared_ptr<Inventory> > inventories;
	std::shared_ptr<InventoryPickup> pickupInventory;

	std::shared_ptr<EntityPlayer> player;
	std::shared_ptr<Mouse> mouse;
	//bool dropItem;

	//std::shared_ptr<GroundItemStack> droppedItemStack;
};

#endif