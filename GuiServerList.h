#ifndef GUISERVERLIST_H
#define GUISERVERLIST_H

#include "GuiText.h"

class GuiServerList
{
public:
	GuiServerList(TTF_Font*, SDL_Color, SDL_Renderer*, std::string, std::string, std::string, std::string, int);

	enum BUTTONSTATE
	{
		NORMAL,
		HOVER,
		CLICK
	};

	SDL_Texture* getTexture(void);
	void setState(int);
	int getState(void);
	std::string getIp(void);
	SDL_Rect getRect(void);
	STATE getOnClick(void);

	void render(void);
	void onEvent(SDL_Event*, const Uint8*);
	bool hasClicked(void);
private:
	GuiText* ipGuiText;
	GuiText* nameGuiText;
	GuiText* descGuiText;
	GuiText* pingGuiText;
	SDL_Texture* texture;
	int state;
	STATE onClick;
	SDL_Rect dest;
	bool clicked;
	std::string ip;
};

#endif