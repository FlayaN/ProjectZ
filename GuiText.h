#ifndef GUITEXT_H
#define GUITEXT_H

#ifdef __APPLE__
	#include <SDL2/SDL.h>
#else
	#include "SDL.h"
	#include "SDL_ttf.h"
	#include "SDL_image.h"
#endif

#include <string>

#include "Utility.h"
#include "Graphics.h"

class GuiText
{
public:
	GuiText(TTF_Font*, SDL_Color, SDL_Renderer*, std::string, int, int);

	SDL_Texture* getTexture(void);
	SDL_Rect getRect(void);
	void render(void);
private:
	SDL_Texture* texture;
	SDL_Rect dest;
};

#endif