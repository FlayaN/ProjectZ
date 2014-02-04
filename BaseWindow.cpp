#include "BaseWindow.h"

BaseWindow::BaseWindow(std::shared_ptr<Graphic> graphicIn)
{
	TTF_Init();
	font = TTF_OpenFont(std::string(Utility::getBasePath() + "assets/fonts/arial.ttf").c_str(), 20);
	fontColor.r = 0;
	fontColor.g = 0;
	fontColor.b = 0;

	graphic = graphicIn;
	running = true;
	newState = false;
	state = STATE::MAINMENU;
}

BaseWindow::~BaseWindow(void)
{

}

void BaseWindow::renderBody(void)
{
	for(int i = 0; i < texts.size(); i++)
	{
		texts[i].render();
	}

	for(int i = 0; i < buttons.size(); i++)
	{
		buttons[i].render();
	}
}

void BaseWindow::render(void)
{
	SDL_SetRenderDrawColor(graphic->getRenderer(), 0xff, 0xff, 0xff, 0xff);
	SDL_RenderClear(graphic->getRenderer());

	renderBody();

	SDL_RenderPresent(graphic->getRenderer());
}

void BaseWindow::onEvent(SDL_Event* ev, const Uint8* keyStates)
{
	switch (ev->type)
	{
		case SDL_QUIT:
		{
			running = false;
			break;
		}
		case SDL_KEYDOWN:
		{
			if(ev->key.keysym.sym == SDLK_ESCAPE)
				running = false;
			break;
		}
	}
	for(int i = 0; i < buttons.size(); i++)
	{
		buttons[i].onEvent(ev, keyStates);
	}
}

void BaseWindow::update(float, const Uint8*)
{
	for(int i = 0; i < buttons.size(); i++)
	{
		if(buttons[i].hasClicked())
		{
			newState = true;
			state = buttons[i].getOnClick();
		}
	}
}

bool BaseWindow::hasNewState(void)
{
	return newState;
}
STATE BaseWindow::requestStateChange(void)
{
	return state;
}

bool BaseWindow::isRunning(void)
{
	return running;
}