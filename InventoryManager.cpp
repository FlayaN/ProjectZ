#include "InventoryManager.h"

InventoryManager::InventoryManager(std::vector<std::shared_ptr<TypeInventory> > typeInventories, std::shared_ptr<EntityPlayer> playerIn)
{
	player = playerIn;
	player->setInventory(std::make_shared<Inventory>(typeInventories[1]));
	pickupInventory = std::make_shared<InventoryPickup>(typeInventories[0]);

	inventories.push_back(pickupInventory);
	inventories.push_back(player->getInventory());

	mouse = std::make_shared<Mouse>();
	//dropItem = false;
}

InventoryManager::~InventoryManager(void)
{
	//droppedItemStack.reset();
	mouse.reset();
}

std::vector<std::shared_ptr<Inventory> > InventoryManager::getInventories(void)
{
	return inventories;
}

std::shared_ptr<InventoryPickup> InventoryManager::getPickupInventory(void)
{
	return pickupInventory;
}

std::shared_ptr<Mouse> InventoryManager::getMouse(void)
{
	return mouse;
}

void InventoryManager::onEvent(SDL_Event* ev, std::HashMap<glm::ivec2, std::shared_ptr<Chunk> >& chunks, std::shared_ptr<Network> net)
{
	switch (ev->type)
	{
		case SDL_KEYUP:
		{
			if(ev->key.keysym.sym == SDLK_i)
			{
				player->toggleInventory();
			}
			break;
		}
		case SDL_MOUSEBUTTONDOWN:
		{
			if(player->hasInventoryOpen())
			{
				if(ev->button.button == SDL_BUTTON_LEFT)
				{
					if(mouse->hasItem())
					{
						bool drop;
						
						for(int i = 0; i < inventories.size(); i++)
						{
							if(inventories[i] != pickupInventory)
							{
								if(!inventories[i]->placeItem(glm::ivec2(ev->button.x, Settings::Graphics::screenHeight - ev->button.y), mouse))
									drop = true;
								else
								{
									drop = false;
									break;
								}
							}
						}

						if(drop)
						{
							std::shared_ptr<GroundItemStack> tmpGroundItem = std::make_shared<GroundItemStack>(mouse->getCurrItemStack()->getItem()->getId(), player->getCenterPosition(), mouse->getCurrItemStack()->getCurrSize());
							mouse->setCurrItemStack(nullptr);
							if(net->getSuccess())
								net->placeItem(tmpGroundItem);
							else
								chunks[Utility::inChunkCoord(player->getCenterPosition())]->addGroundItem(tmpGroundItem);
						}
					}
					else
					{
						for(int i = 0; i < inventories.size(); i++)
						{
							mouse = inventories[i]->pickupItem(glm::ivec2(ev->button.x, Settings::Graphics::screenHeight - ev->button.y));
							if(mouse->getCurrItemStack() != nullptr)
							{
								if(inventories[i] == pickupInventory)
								{
									std::shared_ptr<GroundItemStack> tmpGroundItem = pickupInventory->getGroundItems()[pickupInventory->getCurrHover()];
									if(net->getSuccess())
										net->pickupItem(tmpGroundItem);

									chunks[Utility::inChunkCoord(tmpGroundItem->getPosition())]->removeGroundItem(tmpGroundItem->getId(), tmpGroundItem->getPosition(), tmpGroundItem->getAmount());
								}
								break;
							}
						}
					}
				}
				else if(ev->button.button == SDL_BUTTON_RIGHT)
				{
					for(int i = 0; i < inventories.size(); i++)
					{
						inventories[i]->pickupOneItem(mouse, glm::ivec2(ev->button.x, Settings::Graphics::screenHeight - ev->button.y));
					}
				}
			}
			break;
		}
		case SDL_MOUSEMOTION:
		{
			if(player->hasInventoryOpen())
			{
				mouse->setPosition(glm::vec2(ev->button.x, Settings::Graphics::screenHeight - ev->button.y));
				for(int i = 0; i < inventories.size(); i++)
				{
					inventories[i]->mousePosToIndex(glm::ivec2(ev->button.x, Settings::Graphics::screenHeight - ev->button.y));
				}
			}
			break;
		}
	}
}

/*std::shared_ptr<GroundItemStack> InventoryManager::getDroppedItemStack(void)
{
	return droppedItemStack;
}

void InventoryManager::setDropItem(bool dropItemIn)
{
	dropItem = dropItemIn;
}

bool InventoryManager::getDropItem(void)
{
	return dropItem;
}*/