#ifndef BASEWINDOW_H
#define BASEWINDOW_H

#include <memory>

#include "Graphics.h"
#include "Settings.h"
#include "Defines.h"
#include "GuiButton.h"

class BaseWindow
{
public:
	BaseWindow(void);
	~BaseWindow(void);

	virtual void renderBody(void);
	virtual void render(void);
	virtual void onEvent(SDL_Event*, const Uint8*);
	virtual void update(float, const Uint8*);
	virtual bool hasNewState(void);
	virtual STATE requestStateChange(void);
	virtual bool isRunning(void);
protected:
	SDL_Renderer* renderer;
	std::vector<GuiText> texts;
	std::vector<GuiButton> buttons;
	SDL_Color fontColor;
	TTF_Font* font;
	bool running;
	bool newState;
	STATE state;
};

#endif