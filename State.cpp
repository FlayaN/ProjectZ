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
    
    graphic = std::make_shared<Graphic>(RenderType::SDL);
	setState(STATE::MAINMENU);

	tmpTime = 0;
	currTime = SDL_GetTicks();
	keyStates = SDL_GetKeyboardState(NULL);
	running = true;
	ip = "localhost";
}

void State::setState(STATE newState)
{
    if(state == STATE::MAINMENU && newState == STATE::GAME)
    {
        mainMenu.reset();
        graphic.reset();
        graphic = std::make_shared<Graphic>(RenderType::OGL);
    }
	if(state == STATE::SERVERLIST && newState == STATE::GAME)
    {
        serverList.reset();
        graphic.reset();
        graphic = std::make_shared<Graphic>(RenderType::OGL);
    }
    if(state == STATE::GAME && newState == STATE::MAINMENU)
    {
        game.reset();
        graphic.reset();
        graphic = std::make_shared<Graphic>(RenderType::SDL);
    }

	switch (state)
	{
	case STATE::MAINMENU:
		mainMenu.reset();
		break;
	case STATE::SERVERLIST:
		serverList.reset();
		break;
	case STATE::GAME:
        game.reset();
		break;
	default:
		break;
	}

	switch (newState)
	{
	case STATE::MAINMENU:
		std::cout << "Starting menu" << std::endl;
		mainMenu = std::make_shared<MainMenu>(graphic);
		break;
	case STATE::SERVERLIST:
        std::cout << "Loading serverlist" << std::endl;
		serverList = std::make_shared<ServerList>(graphic);
		break;
	case STATE::GAME:
		std::cout << "Starting game" << std::endl;
		game = std::make_shared<Game>(json, ip, graphic);
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

	requestStateChange();
}

void State::render(void)
{
	switch (state)
	{
	case STATE::MAINMENU:
		mainMenu->render();
		break;
	case STATE::SERVERLIST:
		serverList->render();
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
		mainMenu->update(delta, keyStates);
		break;
	case STATE::SERVERLIST:
		serverList->update(delta, keyStates);
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
		mainMenu->onEvent(ev, keyStates);
		break;
	case STATE::SERVERLIST:
		serverList->onEvent(ev, keyStates);
		break;
	case STATE::GAME:
		game->onEvent(ev, keyStates);
		break;
	default:
		break;
	}
}

void State::requestStateChange(void)
{
	switch (state)
	{
	case STATE::MAINMENU:
		if(mainMenu->hasNewState())
			setState(mainMenu->requestStateChange());
		break;
	case STATE::SERVERLIST:
		if(serverList->hasNewState())
		{
			ip = serverList->getIp();
			setState(serverList->requestStateChange());
		}
		break;
	case STATE::GAME:
		if(game->hasNewState())
			setState(game->requestStateChange());
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
		return mainMenu->isRunning();
		break;
	case STATE::SERVERLIST:
		return serverList->isRunning();
		break;
	case STATE::GAME:
		return game->isRunning();
		break;
	default:
		break;
	}
}