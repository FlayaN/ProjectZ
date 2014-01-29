#ifndef STATE_H
#define STATE_H

#include "Game.h"
#include "Json.h"
#include "MainMenu.h"
#include "Defines.h"

class State
{
public:
	State(void);

	void loop(void);
	void render(void);
	void update(float);
	void onEvent(SDL_Event*);
	bool isRunning(void);
	void setState(STATE);
	void requestStateChange(void);
private:
	std::shared_ptr<Game> game;
	std::shared_ptr<Json> json;
	std::shared_ptr<MainMenu> mainMenu;
	bool running;
	SDL_Event ev;
	STATE state;
	Uint32 oldTime;
	Uint32 currTime;
	float delta;
	float tmpTime;
	const Uint8* keyStates;
};

#endif