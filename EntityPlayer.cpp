#include "EntityPlayer.h"

using namespace std;

EntityPlayer::EntityPlayer(glm::vec2* posIn, glm::vec2 sizeIn, std::string texIn, float speedIn, glm::vec2* bbSizeIn, glm::vec2* bbOffsetIn, std::string bbTexIn) : Entity()
{
	setPosition(posIn);

	speed = speedIn;
	online = false;

	//model = new RectangleShape<Entity>(new glm::vec2(0.0, 0.0), this, sizeIn, texIn);
	size = sizeIn;
	bb = new RectangleShape<Entity>(bbOffsetIn, this, bbSizeIn, bbTexIn);
}

EntityPlayer::~EntityPlayer(void)
{

}

void EntityPlayer::keyDown(SDL_Event* ev)
{
	if(ev->type == SDL_KEYDOWN)
	{

		switch(ev->key.keysym.sym)
		{
		case SDLK_w:
			velocity->y += speed;
			break;
		case SDLK_s:
			velocity->y -= speed;
			break;
		case SDLK_a:
			velocity->x -= speed;
			break;
		case SDLK_d:
			velocity->x += speed;
			break;
		}
	} else if(ev->type == SDL_KEYUP)
	{
		switch(ev->key.keysym.sym)
		{
		case SDLK_w:
			velocity->y -= speed;
			break;
		case SDLK_s:
			velocity->y += speed;
			break;
		case SDLK_a:
			velocity->x += speed;
			break;
		case SDLK_d:
			velocity->x -= speed;
			break;
		}
	}
	
	
	/*float maxVel = 4.0;
	float speed = 0.5;
	
	if(ev->key.keysym.sym == SDLK_w || ev->key.keysym.sym == SDLK_UP) {
		if(velocity->y < maxVel-speed)
			velocity->y += speed;
	} else if(ev->key.keysym.sym == SDLK_s || ev->key.keysym.sym == SDLK_DOWN) {
		if(velocity->y > -(maxVel-speed))
			velocity->y -= speed;
	} else if(ev->key.keysym.sym == SDLK_a || ev->key.keysym.sym == SDLK_LEFT) {
		if(velocity->x > -(maxVel-speed))
			velocity->x -= speed;
	} else if(ev->key.keysym.sym == SDLK_d || ev->key.keysym.sym == SDLK_RIGHT) {
		if(velocity->x < maxVel-speed)
			velocity->x += speed;
	}*/
}

void EntityPlayer::update()
{
	//cout << "Pos X: " << position->x << " Pos Y: " << position->y << " Vel X: " << velocity->x << " Vel Y: " << velocity->y << endl;
	/*
	float friction = 0.01f;

	float border = 0.005;

	if(velocity->x > border)
		velocity->x -= friction;
	else if(velocity->x < -border)
		velocity->x += friction;
	else
		velocity->x = 0.0;

	if(velocity->y > border)
		velocity->y -= friction;
	else if(velocity->y < -border)
		velocity->y += friction;
	else
		velocity->y = 0.0;

	position->x += velocity->x;
	position->y += velocity->y;*/

	position->x += velocity->x;
	position->y += velocity->y;

	//bb->x = position->x;
	//bb->y = position->y;


	//cout << "Pos X: " << position->x << " Pos Y: " << position->y << " Vel X: " << velocity->x << " Vel Y: " << velocity->y << endl;
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