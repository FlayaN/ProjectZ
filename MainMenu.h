#ifndef MAINMENU_H
#define MAINMENU_H

#ifdef __APPLE__
	#include <SDL2/SDL.h>
#else
	#include "SDL.h"
	#include "SDL_ttf.h"
	#include "SDL_image.h"
#endif

#include <memory>

#include "Graphics.h"
#include "Utility.h"
#include "Settings.h"
#include "Defines.h"

struct Text
{
	Text(TTF_Font* font, SDL_Color fontColor, SDL_Renderer* renderer, std::string text, int x, int y)
	{
		SDL_Surface* textImage = TTF_RenderText_Solid(font, text.c_str(), fontColor);
		dest.x = x;
		dest.y = y;
		dest.w = textImage->w;
		dest.h = textImage->h;
		texture = SDL_CreateTextureFromSurface(renderer, textImage);
		SDL_FreeSurface(textImage);
	}
	SDL_Texture* texture;
	SDL_Rect dest;
};

struct Button
{
	Button(TTF_Font* font, SDL_Color fontColor, SDL_Renderer* renderer, std::string textIn, int x, int y, int width, int height, STATE onClickIn)
	{
		texture = IMG_LoadTexture(renderer, std::string(Utility::getBasePath() + "assets/images/button.png").c_str());
		textureHover = IMG_LoadTexture(renderer, std::string(Utility::getBasePath() + "assets/images/buttonHover.png").c_str());
		textureClick = IMG_LoadTexture(renderer, std::string(Utility::getBasePath() + "assets/images/buttonClick.png").c_str());
		text = new Text(font, fontColor, renderer, textIn, x, y);
		dest.x = x;
		dest.y = y;
		dest.h = height;
		dest.w = width;
		state = NORMAL;
		onClick = onClickIn;
	}
	Text* text;
	SDL_Texture* texture;
	SDL_Texture* textureHover;
	SDL_Texture* textureClick;
	int state;
	STATE onClick;
	enum BUTTONSTATE
	{
		NORMAL,
		HOVER,
		CLICK
	};
	SDL_Rect dest;
};

class MainMenu
{
public:
	MainMenu(void);
	~MainMenu(void);

	void render(void);
	void onEvent(SDL_Event*, const Uint8*);
	void update(float, const Uint8*);
	bool hasNewState(void);
	STATE requestStateChange(void);
	bool isRunning(void);
private:
	SDL_Renderer* renderer;
	std::vector<Text> texts;
	std::vector<Button> buttons;
	SDL_Color fontColor;
	TTF_Font* font;
	bool running;
	bool newState;
	STATE state;
};

#endif