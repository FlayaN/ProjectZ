#pragma once

#ifdef __APPLE__
    #include <SDL2/SDL.h>
#else
    #include "SDL.h"
#endif

#include "Tile.h"
#include "EntityPlayer.h"

class Renderer
{
public:
	Renderer(SDL_Window*);
	~Renderer(void);
	void render(Tile* tiles[10][10], EntityPlayer*);
	SDL_Renderer* getRenderer();
private:
	SDL_Renderer *renderer;
	SDL_Window* win;
};

