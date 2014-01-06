#include "EntityPlayer.h"

using namespace std;

EntityPlayer::EntityPlayer(glm::vec2* posIn, glm::vec2* sizeIn, std::string texIn, float speedIn, glm::vec2* bbSizeIn, glm::vec2* bbOffsetIn, std::string bbTexIn) : Entity()
{
	setPosition(posIn);
	tex = TextureManager::getInstance().getTexture(texIn);
	collisionTex = TextureManager::getInstance().getTexture(bbTexIn);
	size = new SDL_Rect();
	size->w = sizeIn->x;
	size->h = sizeIn->y;

	bb = new SDL_Rect();
	bb->w = bbSizeIn->x;
	bb->h = bbSizeIn->y;
	bb->x = bbOffsetIn->x;
	bb->y = bbOffsetIn->y;

	speed = speedIn;
	ready = false;
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
			velocity->y -= speed;
			break;
		case SDLK_s:
			velocity->y += speed;
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
			velocity->y += speed;
			break;
		case SDLK_s:
			velocity->y -= speed;
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

	bb->x = position->x;
	bb->y = position->y;


	//cout << "Pos X: " << position->x << " Pos Y: " << position->y << " Vel X: " << velocity->x << " Vel Y: " << velocity->y << endl;
}

SDL_Texture* EntityPlayer::getTexture(void)
{
	return tex;
}

SDL_Texture* EntityPlayer::getCollisionTexture(void)
{
	return collisionTex;
}

SDL_Rect* EntityPlayer::getSize(void)
{
	return size;
}

SDL_Rect* EntityPlayer::getBB(void)
{
	return bb;
}

glm::vec2 EntityPlayer::getCenterPosition(void)
{
	return glm::vec2(position->x + bb->w/2, position->y + bb->h/2);
}

void EntityPlayer::setId(int idIn)
{
	id = idIn;
	ready = true;
}

int EntityPlayer::getId(void)
{
	return id;
}

bool EntityPlayer::isReady(void)
{
	return ready;
}