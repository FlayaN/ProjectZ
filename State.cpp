#include "State.h"

State::State(void)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		fprintf(stderr, "SDL_Init() failed: %s\n", SDL_GetError());
	}

	if(Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1)
	{
		fprintf(stderr, "Mix_OpenAudio() failed: %s\n", Mix_GetError());
	}

	json = std::make_shared<Json>();

	Graphics::getInstance();
	setState(STATE::GAME);

	tmpTime = 0;
	currTime = SDL_GetTicks();
	keyStates = SDL_GetKeyboardState(NULL);
	running = true;
}

void State::setState(STATE newState)
{
	switch (newState)
	{
	case STATE::MAINMENU:
		break;
	case STATE::SERVERLIST:
		break;
	case STATE::GAME:
		game = std::make_shared<Game>(json);
		break;
	default:
		break;
	}
	state = newState;
}

void State::loop(void)
{
	oldTime = currTime;
	currTime = SDL_GetTicks();
	delta = (currTime - oldTime) / 1000.0f;

	while(SDL_PollEvent(&ev)) 
	{
		onEvent(&ev);
	}

	update(delta);

	render();
}

void State::render(void)
{
	switch (state)
	{
	case STATE::MAINMENU:
		break;
	case STATE::SERVERLIST:
		break;
	case STATE::GAME:
		game->render();
		break;
	default:
		break;
	}
}

void State::update(float delta)
{
	switch (state)
	{
	case STATE::MAINMENU:
		break;
	case STATE::SERVERLIST:
		break;
	case STATE::GAME:
		game->update(delta, keyStates);
		break;
	default:
		break;
	}
}

void State::onEvent(SDL_Event* ev)
{
	switch (state)
	{
	case STATE::MAINMENU:
		break;
	case STATE::SERVERLIST:
		break;
	case STATE::GAME:
		game->onEvent(ev, keyStates);
		break;
	default:
		break;
	}
}

bool State::isRunning(void)
{
	switch (state)
	{
	case STATE::MAINMENU:
		break;
	case STATE::SERVERLIST:
		break;
	case STATE::GAME:
		return game->isRunning();
		break;
	default:
		break;
	}
}