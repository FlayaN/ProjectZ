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
	for(int x = -ChunkAmount/2; x <= ChunkAmount/2; x++)
	{
		for(int y = -ChunkAmount/2; y <= ChunkAmount/2; y++)
		{
			Chunk* chunk = new Chunk(new Vec2(x, y));
			
			std::stringstream ss;
			ss << "res/" << (i%9)+1 << ".png";

			chunk->init(renderer->getRenderer(), ss.str());
			chunks[Vec2(x, y)] = chunk;
			i++;
		}
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
	std::vector<std::pair<Tile*, Vec2> > v = ChunkUtility::getSurroundingTiles(chunks, CollisionDistance, player->getPosition());
    
	//std::cout << "surroundingTiles size: " << v.size() << std::endl;

    for(auto tile: v)
    {
        
        Tile* currTile = tile.first;
        Vec2 tileCoord = tile.second;
        
		if(currTile != nullptr)
		{
			SDL_Rect playerBB = *player->getBB();
			playerBB.y -= playerBB.h;
			SDL_Rect* bb = currTile->getBB();
			if(bb != nullptr)
			{
				bb->x = (tileCoord.x)*bb->w;
				bb->y = (tileCoord.y)*(bb->h);
			}

			//CollisionHandler::intersects(&playerBB, bb);

			if(CollisionHandler::intersects(&playerBB, bb))
				std::cout << "COLLISION!" << std::endl;
			//else
			//	std::cout << "NO COLLISION!" << std::endl;
		}
    }
}