#ifndef GUIBUTTON_H
#define GUIBUTTON_H

#include "GuiText.h"

class GuiButton
{
public:
	GuiButton(TTF_Font*, SDL_Color, SDL_Renderer*, std::string, int, int, int, int, STATE);

	enum BUTTONSTATE
	{
		NORMAL,
		HOVER,
		CLICK
	};

	SDL_Texture* getTexture(void);
	SDL_Texture* getTextureHover(void);
	SDL_Texture* getTextureClick(void);
	void setState(int);
	int getState(void);
	GuiText* getGuiText(void);
	SDL_Rect getRect(void);
	STATE getOnClick(void);

	void render(void);
	void onEvent(SDL_Event*, const Uint8*);
	bool hasClicked(void);
private:
	GuiText* text;
	SDL_Texture* texture;
	SDL_Texture* textureHover;
	SDL_Texture* textureClick;
	int state;
	STATE onClick;
	SDL_Rect dest;
	bool clicked;
};

#endif