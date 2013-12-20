#include "EntityPlayer.h"

using namespace std;

EntityPlayer::EntityPlayer(SDL_Renderer* ren) : Entity()
{
	tex = IMG_LoadTexture(ren, "res/mario.gif");
	collisionTex = IMG_LoadTexture(ren, "res/block2.png");
	size = new SDL_Rect();
	size->h = 200;
	size->w = 100;

	//bb = new Shape(new Vec3(), position);
	

	bb = new SDL_Rect();
	bb->h = 50;
	bb->w = 100;
	bb->x = 0;
	bb->y = 0;
}

EntityPlayer::~EntityPlayer(void)
{

}

void EntityPlayer::keyDown(SDL_Event* ev)
{
	
	float speed = 0.1;

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