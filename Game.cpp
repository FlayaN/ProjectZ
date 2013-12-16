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

	int i = 0;
	for(int x = 0; x < 3; x++)
	{
		for(int y = 0; y < 3; y++)
		{
			Chunk* chunk = new Chunk();

			std::stringstream ss;
			ss << "res/" << i+1 << ".png";

			chunk->init(renderer->getRenderer(), ss.str());
			chunks[Coord(x, y)] = chunk;
			i++;
		}
	}

	/*for(int i = 0; i < 9; i++)
	{
		Chunk* chunk = new Chunk();

		std::stringstream ss;
		ss << "res/" << i+1 << ".png";

		chunk->init(renderer->getRenderer(), ss.str());
		chunks[i] = chunk;
	}*/

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
		collision();
		player->update();

		//Rendering
		render();
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

void Game::render()
{
	renderer->render(chunks, player);
}

void Game::collision(void)
{
	Chunk* currChunk = getChunk(player->getPosition());
	if(currChunk != nullptr)
	{
		Tile* currTile = getTile(currChunk->getTiles(), player->getPosition());
		if(currTile != nullptr)
		{
			std::cout << "test" << std::endl;
			if(CollisionHandler::intersects(player->getBB(), currTile->getBB()))
				std::cout << "COLLIDING" << std::endl;
			else
				std::cout << "No Collision" << std::endl;
		}
	}
}

Chunk* Game::getChunk(Vec3* coord)
{
	Coord c = Coord((int)(coord->x/ChunkSize), (int)((coord->y/ChunkSize)));
	std::cout << "Chunk X: " << c.x << " Chunk Y: " << c.y << std::endl;
	return chunks[c];
}

Tile* Game::getTile(std::HashMap<Coord, Tile*> tiles, Vec3* coord)
{
	Coord c = Coord((int)(coord->x/TileSize), (int)((coord->y/TileSize)*2));
	std::cout << "Tile X: " << c.x << " Tile Y: " << c.y << std::endl;
	return tiles[c];
}