#include "EntityPlayer.h"

/*EntityPlayer::EntityPlayer(glm::vec2* posIn, float rotIn, glm::vec2 sizeIn, std::string texIn, glm::vec2* bbSizeIn, glm::vec2* bbOffsetIn, std::string bbTexIn, float accelerationIn, float maxSpeedIn, float frictionIn) : MovingEntity()
{
	setPosition(posIn);
	setRotation(rotIn);
	acceleration = accelerationIn;
	maxSpeed = maxSpeedIn;
	friction = frictionIn;
	online = false;

	size = sizeIn;
	bb = new RectangleShape(bbOffsetIn, 0.0, bbSizeIn, bbTexIn);
}*/
EntityPlayer::EntityPlayer(TypePlayer playerType)
{
	*position = playerType.startPos;
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
		getVelocity()->y += acceleration;
	if(keyCode[SDL_SCANCODE_S])
		getVelocity()->y -= acceleration;
	if(keyCode[SDL_SCANCODE_A])
		getVelocity()->x -= acceleration;
	if(keyCode[SDL_SCANCODE_D])
		getVelocity()->x += acceleration;

	if(std::abs(getVelocity()->x) > maxSpeed)
	{
		if(getVelocity()->x > 0)
			getVelocity()->x = maxSpeed;
		else if(getVelocity()->x < 0)
			getVelocity()->x = -maxSpeed;
	}

	if(std::abs(getVelocity()->y) > maxSpeed)
	{
		if(getVelocity()->y > 0)
			getVelocity()->y = maxSpeed;
		else if(getVelocity()->y < 0)
			getVelocity()->y = -maxSpeed;
	}

	if(!keyCode[SDL_SCANCODE_A] && !keyCode[SDL_SCANCODE_D])
	{
		if(getVelocity()->x > 0)
			getVelocity()->x -= friction*delta;
		else if(getVelocity()->x < 0)
			getVelocity()->x += friction*delta;
	}

	if(!keyCode[SDL_SCANCODE_W] && !keyCode[SDL_SCANCODE_S])
	{
		if(getVelocity()->y > 0)
			getVelocity()->y -= friction*delta;
		else if(getVelocity()->y < 0)
			getVelocity()->y += friction*delta;
	}
	
	position->x += getVelocity()->x * delta;
	position->y += getVelocity()->y * delta;
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