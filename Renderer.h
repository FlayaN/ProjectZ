#pragma once

#ifdef __APPLE__
    #include <SDL2/SDL.h>
#else
    #include "SDL.h"
#endif

#include "Defines.h"
#include "Chunk.h"
#include "EntityPlayer.h"

class Renderer
{
public:
	Renderer(SDL_Window*);
	~Renderer(void);
	void render(std::HashMap<int, Chunk*> , EntityPlayer*);
	SDL_Renderer* getRenderer(void);
private:
	SDL_Renderer *renderer;
	SDL_Window* win;
};