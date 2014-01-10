#include "EntityPlayer.h"

using namespace std;

EntityPlayer::EntityPlayer(glm::vec2* posIn, glm::vec2 sizeIn, std::string texIn, glm::vec2* bbSizeIn, glm::vec2* bbOffsetIn, std::string bbTexIn, float accelerationIn, float maxSpeedIn, float frictionIn) : Entity()
{
	setPosition(posIn);

	acceleration = accelerationIn;
	maxSpeed = maxSpeedIn;
	friction = frictionIn;
	online = false;

	size = sizeIn;
	bb = new RectangleShape<Entity>(bbOffsetIn, this, bbSizeIn, bbTexIn);
}

EntityPlayer::~EntityPlayer(void)
{

}

void EntityPlayer::update(float delta, const Uint8* keyCode)
{
	if(keyCode[SDL_SCANCODE_W])
		velocity->y += acceleration;
	if(keyCode[SDL_SCANCODE_S])
		velocity->y -= acceleration;
	if(keyCode[SDL_SCANCODE_A])
		velocity->x -= acceleration;
	if(keyCode[SDL_SCANCODE_D])
		velocity->x += acceleration;

	if(std::abs(velocity->x) > maxSpeed)
	{
		if(velocity->x > 0)
			velocity->x = maxSpeed;
		else if(velocity->x < 0)
			velocity->x = -maxSpeed;
	}

	if(std::abs(velocity->y) > maxSpeed)
	{
		if(velocity->y > 0)
			velocity->y = maxSpeed;
		else if(velocity->y < 0)
			velocity->y = -maxSpeed;
	}

	if(!keyCode[SDL_SCANCODE_A] && !keyCode[SDL_SCANCODE_D])
	{
		if(velocity->x > 0)
			velocity->x -= friction*delta;
		else if(velocity->x < 0)
			velocity->x += friction*delta;
	}

	if(!keyCode[SDL_SCANCODE_W] && !keyCode[SDL_SCANCODE_S])
	{
		if(velocity->y > 0)
			velocity->y -= friction*delta;
		else if(velocity->y < 0)
			velocity->y += friction*delta;
	}
	
	position->x += velocity->x * delta;
	position->y += velocity->y * delta;
}

glm::vec2 EntityPlayer::getCenterPosition(void)
{
	return glm::vec2(position->x + bb->getWidth()/2, position->y + bb->getHeight()/2);
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

RectangleShape<Entity>* EntityPlayer::getBB(void)
{
	return bb;
}