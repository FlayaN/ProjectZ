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

	void setState(int);
	int getState(void);
	std::string getIp(void);
	SDL_Rect getRect(void);
	STATE getOnClick(void);
	void setPing(int);

	void render(void);
	void onEvent(SDL_Event*, const Uint8*);
	bool hasClicked(void);
private:
	GuiText* ipGuiText;
	GuiText* nameGuiText;
	GuiText* descGuiText;
	GuiText* pingGuiText;
	SDL_Texture* edgeTexture;
	SDL_Texture* texture;
	SDL_Texture* textureHover;
	SDL_Texture* textureClick;
	int state;
	STATE onClick;
	SDL_Rect middle;
	SDL_Rect leftEdge;
	SDL_Rect rightEdge;
	SDL_Rect rect;
	bool clicked;
	std::string ip;
};

#endif