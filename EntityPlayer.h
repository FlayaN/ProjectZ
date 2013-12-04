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

	SDL_Texture* getTexture();
	SDL_Rect* getRect();

private:
	SDL_Texture* tex;
	SDL_Rect* rect;
};

