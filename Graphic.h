#ifndef GRAPHIC_H
#define GRAPHIC_H

#ifdef __APPLE__
	#include <SDL2/SDL.h>
	#include <SDL2_image/SDL_image.h>
#else
	#include "SDL.h"
	#include "SDL_image.h"
#endif

#include <iostream>

#include "GL_utilities.h"
#include "Defines.h"

enum class RenderType
{
    SDL,
    OGL
};

class Graphic
{
public:
    Graphic(RenderType);
    ~Graphic(void);
	SDL_Window* getWindow(void);
	SDL_Renderer* getRenderer(void);
	SDL_GLContext getContext(void);
private:
	SDL_Window* win;
	SDL_Renderer* renderer;
	SDL_GLContext context;
};

#endif