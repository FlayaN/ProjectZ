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
        
        SDL_RenderClear(renderer->getRenderer());
        render();
		collision();
        SDL_RenderPresent(renderer->getRenderer());
        
		player->update();

		//Rendering
		//render();
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
    int w,h;
	SDL_GetWindowSize(win, &w, &h);
    
    //SDL_RenderClear(renderer->getRenderer());
    std::pair<Chunk*, Vec2> chunkPair = getChunk(player->getPosition());
    
	Chunk* currChunk = chunkPair.first;
    Vec2 chunkCoord = chunkPair.second;
    
	if(currChunk != nullptr)
	{
        std::pair<Tile*, Vec2> tilePair = getTile(currChunk->getTiles(), player->getPosition());
        
        Tile* currTile = tilePair.first;
        Vec2 tileCoord = tilePair.second;
        
		if(currTile != nullptr)
		{
			//std::cout << "test" << std::endl;
            
            //renderTexture(player->getTexture(), renderer, rect);
            
            float playerX = -player->getPosition()->x + w/2 - player->getSize()->w/2;
            float playerY = -player->getPosition()->y + h/2 - player->getSize()->h/2;
            
            SDL_Rect playerBB = *player->getBB();
            //playerBB->x -= player->getSize()->w/2;
            playerBB.y += 150;
            
            SDL_Rect renderPlayerBB = playerBB;
            renderPlayerBB.x = w/2 - player->getSize()->w/2;
            renderPlayerBB.y = h/2 + player->getSize()->h/2 - renderPlayerBB.h;
            
            SDL_RenderCopy(renderer->getRenderer(), IMG_LoadTexture(renderer->getRenderer(), "res/block.png"), NULL, &renderPlayerBB);
            
            SDL_Rect* bb = currTile->getBB();
            
            if(bb != nullptr)
            {
                //bb->x = (chunkCoord.x)*ChunkSize + (tileCoord.x+1)*TileSize;
                //bb->y = (chunkCoord.y)*ChunkSize + (tileCoord.y+1)*TileSize;
                
                SDL_Rect copy = *bb;
                
                copy.x = ((chunkCoord.x*3)+tileCoord.x)*copy.w + playerX;
                copy.y = ((chunkCoord.y*3)+tileCoord.y)*(copy.h) + playerY;
                
                bb->x = ((chunkCoord.x*3)+tileCoord.x)*bb->w;
                bb->y = ((chunkCoord.y*3)+tileCoord.y)*(bb->h);
                
                //std::cout << "bbX: " << bb->x << " bbY: " << bb->y << std::endl;
                //std::cout << "copyX: " << copy.x << " copyY: " << copy.y << std::endl;
                //bb->x = w/2 - bb->w/2;
                //bb->y = h/2 - bb->h/2;
                
                //std::cout << "bb X: " << bb->x << " bb Y: " << bb->y << " bb W: " << bb->w << " bb H: " << bb->h <<std::endl;
                
                SDL_RenderCopy(renderer->getRenderer(), IMG_LoadTexture(renderer->getRenderer(), "res/block.png"), NULL, &copy);
            }
            
            if(CollisionHandler::intersects(&playerBB, bb))
                std::cout << "COLLIDING" << std::endl;
            else
                std::cout << "No Collision" << std::endl;
		}
	}
    //SDL_RenderPresent(renderer->getRenderer());
}

std::pair<Chunk*, Vec2> Game::getChunk(Vec3* coord)
{
	Coord c = Coord((int)(coord->x/ChunkSize), (int)(((coord->y+200)/(ChunkSize/2))));
    //TODO Add support for multiple chunks for detection
	//std::cout << "Chunk X: " << c.x << " Chunk Y: " << c.y << std::endl;
	return std::make_pair(chunks[c], Vec2(c.x, c.y));
}

std::pair<Tile*, Vec2> Game::getTile(std::HashMap<Coord, Tile*> tiles, Vec3* coord)
{
	Coord c = Coord((int)((int)coord->x%ChunkSize), (int)(((int)(coord->y+200)%(ChunkSize/2))));
    //TODO Add support for multiple tiles for detection
    c.x /= TileSize;
    c.y /= TileSize/2;
	//std::cout << "Tile X: " << c.x << " Tile Y: " << c.y << std::endl;
	return std::make_pair(tiles[c], Vec2(c.x, c.y));
}