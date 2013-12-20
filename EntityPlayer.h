#pragma once

#ifdef __APPLE__
	#include <SDL2/SDL.h>
	#include <SDL2_image/SDL_image.h>
#else
	#include "SDL.h"
	#include "SDL_image.h"
#endif

#include "entity.h"
#include <iostream>

class EntityPlayer : public Entity {
public:
	EntityPlayer(SDL_Renderer*);
	~EntityPlayer(void);
	void keyDown(SDL_Event*);
	void update();

	SDL_Texture* getTexture(void);
	SDL_Texture* getCollisionTexture(void);
	SDL_Rect* getSize(void);
	SDL_Rect* getBB(void);
private:
	SDL_Texture* tex;
	SDL_Texture* collisionTex;
	SDL_Rect* size;
	//Shape* bb;

	SDL_Rect* bb;
};

