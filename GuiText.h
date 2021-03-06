#ifndef GUITEXT_H
#define GUITEXT_H

#ifdef __APPLE__
	#include <SDL2/SDL.h>
    #include <SDL2_image/SDL_image.h>
    #include <SDL2_ttf/SDL_ttf.h>
#else
	#include "SDL.h"
	#include "SDL_ttf.h"
	#include "SDL_image.h"
#endif

#include <string>

#include "Utility.h"

class GuiText
{
public:
	GuiText(TTF_Font*, SDL_Color, SDL_Renderer*, std::string, int, int);
	void setText(std::string);
	SDL_Texture* getTexture(void);
	SDL_Rect getRect(void);
	void render(void);
private:
	SDL_Texture* texture;
	SDL_Rect dest;
	TTF_Font* font;
	SDL_Color fontColor;
	SDL_Renderer* renderer;
};

#endif