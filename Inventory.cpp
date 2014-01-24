#include "Inventory.h"

Inventory::Inventory(int maxSizeIn, glm::ivec2 posIn) : maxSize(maxSizeIn), pos(posIn)
{
	for(int i = 0; i < maxSize; i++)
		inv.push_back(nullptr);
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
				std::shared_ptr<ItemStack> tmpItemStack = std::make_shared<ItemStack>(ItemStack(item->getStackSize()));
				tmpItemStack->setItem(item);
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

std::shared_ptr<MouseItem> Inventory::pickupItem(glm::ivec2 mouse)
{
	std::shared_ptr<MouseItem> tmpMouseItem = std::make_shared<MouseItem>();
	int index = mousePosToIndex(mouse);

	if(index != -1)
	{
		std::cout << "Pickup item" << std::endl;
		tmpMouseItem->setCurrItem(inv.at(index));
		tmpMouseItem->setPosition((glm::vec2)mouse);
		inv.at(index) = nullptr;
	}
	else
	{
		tmpMouseItem->setCurrItem(nullptr);
	}
	return tmpMouseItem;
}

void Inventory::pickupOneItem(std::shared_ptr<MouseItem> currMouseItem, glm::ivec2 mouse)
{
	int index = mousePosToIndex(mouse);

	if(index != -1)
	{
		if(inv.at(index) != nullptr)
		{
			if(currMouseItem->getCurrItem() == nullptr)
			{
				//std::cout << "Pickup item" << std::endl;
				std::shared_ptr<ItemStack> tmpItemStack = std::make_shared<ItemStack>(inv.at(index)->getMaxSize());
				tmpItemStack->setItem(inv.at(index)->getItem());
				tmpItemStack->increaseStack();
				currMouseItem->setCurrItem(tmpItemStack);
				currMouseItem->setPosition((glm::vec2)mouse);
				inv.at(index)->decreaseStack();
				if(inv.at(index)->getCurrSize() < 1)
					inv.at(index) = nullptr;
			}
			else
			{
				if(currMouseItem->getCurrItem()->getItem()->getId() == inv.at(index)->getItem()->getId())
				{

					if(currMouseItem->getCurrItem()->increaseStack())
					{
						inv.at(index)->decreaseStack();
						if(inv.at(index)->getCurrSize() < 1)
							inv.at(index) = nullptr;
					}
				}
			}
		}
		/*else
		{
			if(currMouseItem->getCurrItem() != nullptr)
			{
				std::shared_ptr<ItemStack> tmpItemStack = std::make_shared<ItemStack>(currMouseItem->getCurrItem()->getMaxSize());
				tmpItemStack->setItem(currMouseItem->getCurrItem()->getItem());
				tmpItemStack->increaseStack();
				inv.at(index) = tmpItemStack;
				currMouseItem->getCurrItem()->decreaseStack();
				if(currMouseItem->getCurrItem()->getCurrSize() < 1)
					currMouseItem->setCurrItem(nullptr);
			}
		}*/
	}
	else
	{
		currMouseItem->setCurrItem(nullptr);
	}
}

void Inventory::placeItem(glm::ivec2 mouse, std::shared_ptr<MouseItem> mouseItem)
{
	int index = mousePosToIndex(mouse);

	if(index != -1)
	{
		if(inv.at(index) == nullptr)
		{
			std::cout << "PlaceItem in Empty slot" << std::endl;
			inv.at(index) = mouseItem->getCurrItem();
			mouseItem->setCurrItem(nullptr);
		}
		else
		{
			if(inv.at(index)->getItem()->getId() == mouseItem->getCurrItem()->getItem()->getId())
			{
				std::cout << "Same Item so stack them together and give remainder to hand" << std::endl;
				mouseItem->setCurrItem(inv.at(index)->addItemStack(mouseItem->getCurrItem()));
			}
			else
			{
				std::cout << "Replace hand with slot" << std::endl;
				std::shared_ptr<ItemStack> tmp = inv.at(index);
				inv.at(index) = mouseItem->getCurrItem();
				mouseItem->setCurrItem(tmp);
			}
		}
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
