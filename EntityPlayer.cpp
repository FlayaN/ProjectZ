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

void EntityPlayer::keyDown(SDL_Event* ev)
{
	glm::vec2 tmpVel = *velocity;

	if(ev->type == SDL_KEYDOWN)
	{
		switch(ev->key.keysym.sym)
		{
		case SDLK_w:
			tmpVel.y += acceleration;
			break;
		case SDLK_s:
			tmpVel.y -= acceleration;
			break;
		case SDLK_a:
			tmpVel.x -= acceleration;
			break;
		case SDLK_d:
			tmpVel.x += acceleration;
			break;
		}
	} else if(ev->type == SDL_KEYUP)
	{
		switch(ev->key.keysym.sym)
		{
		case SDLK_w:
			tmpVel.y -= acceleration;
			break;
		case SDLK_s:
			tmpVel.y += acceleration;
			break;
		case SDLK_a:
			tmpVel.x += acceleration;
			break;
		case SDLK_d:
			tmpVel.x -= acceleration;
			break;
		}
	}

	std::cout << "tmpVel.x: " << tmpVel.x << " tmpVel.y: " << tmpVel.y << std::endl;

	if(std::abs(tmpVel.x) < maxSpeed)
		velocity->x = tmpVel.x;

	if(std::abs(tmpVel.y) < maxSpeed)
		velocity->y = tmpVel.y;
}

void EntityPlayer::update(float delta)
{
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