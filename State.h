#ifndef STATE_H
#define STATE_H

#include "Game.h"
#include "Json.h"

enum class STATE
{
	MAINMENU,
	SERVERLIST,
	GAME
};

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
private:
	std::shared_ptr<Game> game;
	std::shared_ptr<Json> json;
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