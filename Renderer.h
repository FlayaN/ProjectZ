#pragma once

#ifdef __APPLE__
    #include <SDL2/SDL.h>
#else
    #include "SDL.h"
#endif

#include "Defines.h"
#include "ChunkUtility.h"
#include "EntityPlayer.h"

class Renderer
{
public:
	Renderer(SDL_Window*);
	~Renderer(void);
	void render(std::HashMap<Vec2, Chunk*> , EntityPlayer*);
	SDL_Renderer* getRenderer(void);
private:
	SDL_Renderer *renderer;
	SDL_Window* win;
};