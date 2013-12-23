#include "Game.h"

Game::Game(void) : _running(false)
{
    
}

Game::~Game(void)
{
    destroy();
}

int Game::init(void)
{
	// Initialize the SDL library.
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		fprintf(stderr, "SDL_Init() failed: %s\n", SDL_GetError());
		return APP_FAILED;
	}
	
	
	renderer = new Renderer();
	//Graphics::getInstance().init(width, height);

	//int i = 0;
	for(int x = -ChunkAmount/2; x <= ChunkAmount/2; x++)
	{
		for(int y = -ChunkAmount/2; y <= ChunkAmount/2; y++)
		{
			Chunk* chunk = new Chunk(new Vec2(x, y));
			
			std::stringstream ss;
			//ss << "res/" << (i%9)+1 << ".png";
			ss << "res/" << Utility::getRandInt(1, 9) << ".png";
			chunk->init(ss.str());
			chunks[Vec2(x, y)] = chunk;
			//i++;
		}
	}

	player = new EntityPlayer();
	return APP_OK;
}

void Game::destroy()
{
	/*if (win)
	{
		SDL_DestroyWindow(win);
		SDL_DestroyRenderer(renderer->getRenderer());
		SDL_Quit();
	}*/
}

int Game::run(void)
{
	// Initialize application.
	int state = init();
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
	std::vector<Tile*> v = ChunkUtility::getSurroundingTiles(chunks, CollisionDistance, player);
	
	for(auto tile: v)
    {
		Tile* currTile = tile;
		Vec2 tileCoord = *currTile->getCoord();
		
		if(currTile != nullptr)
		{
			SDL_Rect* bb = currTile->getBB();
			if(bb != nullptr)
			{
				bb->x = (tileCoord.x)*bb->w;
				bb->y = (tileCoord.y)*(bb->h);
			}
			//CollisionHandler::intersects(&playerBB, bb);

			if(CollisionHandler::intersects(player->getBB(), bb))
			{
				std::cout << "Collision at X: " << bb->x << " Y: " << bb->y << std::endl;
			}
		}
	}
}