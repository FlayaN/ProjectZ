#include "EntityPlayer.h"

EntityPlayer::EntityPlayer(TypePlayer playerType)
{
	position = playerType.startPos;
	rotation = playerType.rotation;
	acceleration = playerType.acceleration;
	maxSpeed = playerType.maxSpeed;
	size = playerType.size;
	texture = playerType.texture;
	
	online = false;
	bb = new RectangleShape(new glm::vec2(0, 0), 0.0, new glm::vec2(playerType.size.x, playerType.size.y/4)); //TODO BOUNDINGBOXES

	inventory = std::make_shared<Inventory>(Inventory(27, glm::ivec2(200, 200)));
	mouseItem = std::make_shared<MouseItem>(MouseItem());
	inventoryOpen = false;
	draggingItem = false;
}

EntityPlayer::~EntityPlayer(void)
{

}

void EntityPlayer::onEvent(SDL_Event* ev)
{
	switch (ev->type)
	{
		case SDL_KEYUP:
		{
			if(ev->key.keysym.sym == SDLK_i)
			{
				inventoryOpen = !inventoryOpen;
			}
			break;
		}
		case SDL_MOUSEBUTTONDOWN:
			if(inventoryOpen)
			{
				if(ev->button.button == SDL_BUTTON_LEFT)
				{
					if(mouseItem->getCurrItem() != nullptr)
					{
						inventory->placeItem(glm::ivec2(ev->button.x, Settings::Graphics::screenHeight - ev->button.y), mouseItem);
						if(mouseItem->getCurrItem() == nullptr)
						{
							draggingItem = false;
						}
					}
					else
					{
						mouseItem = inventory->pickupItem(glm::ivec2(ev->button.x, Settings::Graphics::screenHeight - ev->button.y));
						if(mouseItem->getCurrItem() != nullptr)
						{
							draggingItem = true;
						}
					}
				}
				if(ev->button.button == SDL_BUTTON_RIGHT)
				{

				}
			}
			break;
		case SDL_MOUSEBUTTONUP:
			if(inventoryOpen)
			{
				if(ev->button.button == SDL_BUTTON_LEFT)
				{

				}
				if(ev->button.button == SDL_BUTTON_RIGHT)
				{

				}
			}
			break;
		case SDL_MOUSEMOTION:
			if(draggingItem)
			{
				mouseItem->setPosition(glm::vec2(ev->button.x, Settings::Graphics::screenHeight - ev->button.y));
			}
			break;
	}
}

void EntityPlayer::update(float delta, const Uint8* keyCode)
{
	if(keyCode[SDL_SCANCODE_W])
		velocity.y += acceleration;
	if(keyCode[SDL_SCANCODE_S])
		velocity.y -= acceleration;
	if(keyCode[SDL_SCANCODE_A])
		velocity.x -= acceleration;
	if(keyCode[SDL_SCANCODE_D])
		velocity.x += acceleration;

	if(std::abs(velocity.x) > maxSpeed)
	{
		if(velocity.x > 0)
			velocity.x = maxSpeed;
		else if(velocity.x < 0)
			velocity.x = -maxSpeed;
	}

	if(std::abs(velocity.y) > maxSpeed)
	{
		if(velocity.y > 0)
			velocity.y = maxSpeed;
		else if(velocity.y < 0)
			velocity.y = -maxSpeed;
	}

	if(!keyCode[SDL_SCANCODE_A] && !keyCode[SDL_SCANCODE_D])
	{
		if(velocity.x > 0)
			velocity.x -= friction*delta;
		else if(velocity.x < 0)
			velocity.x += friction*delta;
	}

	if(!keyCode[SDL_SCANCODE_W] && !keyCode[SDL_SCANCODE_S])
	{
		if(velocity.y > 0)
			velocity.y -= friction*delta;
		else if(velocity.y < 0)
			velocity.y += friction*delta;
	}

	if(abs(velocity.x) < 0.5)
		velocity.x = 0;

	if(abs(velocity.y) < 0.5)
		velocity.y = 0;
	
	position.x += velocity.x * delta;
	position.y += velocity.y * delta;
}

glm::vec2 EntityPlayer::getCenterPosition(void)
{
	return glm::vec2(position.x + bb->getWidth()/2, position.y + bb->getHeight()/2);
}

void EntityPlayer::setId(int idIn)
{
	id = idIn;
	online = true;
}

int EntityPlayer::getId(void)
{
	return id;
}

bool EntityPlayer::isOnline(void)
{
	return online;
}

glm::vec2 EntityPlayer::getSize(void)
{
	return size;
}

RectangleShape* EntityPlayer::getBB(void)
{
	return bb;
}

std::string EntityPlayer::getTexture(void)
{
	return texture;
}

void EntityPlayer::setFriction(float frictionIn)
{
	friction = frictionIn;
}

bool EntityPlayer::hasInventoryOpen(void)
{
	return inventoryOpen;
}

std::shared_ptr<Inventory> EntityPlayer::getInventory(void)
{
	return inventory;
}

bool EntityPlayer::isDraggingItem(void)
{
	return draggingItem;
}

std::shared_ptr<MouseItem> EntityPlayer::getMouseItem(void)
{
	return mouseItem;
}