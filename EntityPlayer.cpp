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
}

EntityPlayer::~EntityPlayer(void)
{

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