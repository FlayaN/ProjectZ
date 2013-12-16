#include "Game.h"

Game::Game() : _running(false)
{
    
}

Game::~Game()
{
    destroy();
}

int Game::init(int width, int height)
{
	// Initialize the SDL library.
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		fprintf(stderr, "SDL_Init() failed: %s\n", SDL_GetError());
		return APP_FAILED;
	}
	
	win = SDL_CreateWindow("Project Z", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
	renderer = new Renderer(win);
	for(int i = 0; i < 9; i++)
	{
		Chunk* chunk = new Chunk();

		std::stringstream ss;
		ss << "res/" << i+1 << ".png";

		chunk->init(renderer->getRenderer(), ss.str());
		chunks[i] = chunk;
	}

	player = new EntityPlayer(renderer->getRenderer());
	return APP_OK;
}

void Game::destroy()
{
	if (win)
	{
		SDL_DestroyWindow(win);
		SDL_DestroyRenderer(renderer->getRenderer());
		SDL_Quit();
	}
}

int Game::run(int width, int height)
{
	// Initialize application.
	int state = init(width, height);
	if (state != APP_OK) return state;
	
	// Enter to the SDL event loop.
	SDL_Event ev;
	_running = true;

	while(_running)
	{
		//Events
		while( SDL_PollEvent(&ev)) 
		{
			player->keyDown(&ev);
			onEvent(&ev);
		}

		//Logic
		player->update();

		//Rendering
		Render();
	}
	
	return APP_OK;
}

void Game::onEvent(SDL_Event* ev)
{
	switch (ev->type)
	{
		case SDL_QUIT:
			_running = false;
			break;
			
		case SDL_KEYDOWN:
		{
			if (ev->key.keysym.sym == SDLK_ESCAPE)
			{
				_running = false;
			}
		}
	}
}

void Game::Render()
{
	renderer->render(chunks, player);
}