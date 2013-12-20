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
			Chunk* chunk = new Chunk(new Vec2(x, y));

			std::stringstream ss;
			ss << "res/" << i+1 << ".png";

			chunk->init(renderer->getRenderer(), ss.str());
			chunks[Vec2(x, y)] = chunk;
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
        //render();
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
    
    //Vec2* playerPos = player->getPosition();
    
    std::vector<std::pair<Tile*, Vec2> > v = getSurroundingTiles(2, player->getPosition());
    
    for(auto tile: v)
    {
        
        Tile* currTile = tile.first;
        Vec2 tileVec2 = tile.second;
        
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
                //bb->x = (chunkVec2.x)*ChunkSize + (tileVec2.x+1)*TileSize;
                //bb->y = (chunkVec2.y)*ChunkSize + (tileVec2.y+1)*TileSize;
                
                SDL_Rect copy = *bb;
                
                copy.x = (tileVec2.x)*copy.w + playerX;
                copy.y = (tileVec2.y)*(copy.h) + playerY;
                
                bb->x = (tileVec2.x)*bb->w;
                bb->y = (tileVec2.y)*(bb->h);
                
                //std::cout << "bbX: " << bb->x << " bbY: " << bb->y << std::endl;
                //std::cout << "copyX: " << copy.x << " copyY: " << copy.y << std::endl;
                //bb->x = w/2 - bb->w/2;
                //bb->y = h/2 - bb->h/2;
                
                //std::cout << "bb X: " << bb->x << " bb Y: " << bb->y << " bb W: " << bb->w << " bb H: " << bb->h <<std::endl;
                
                SDL_RenderCopy(renderer->getRenderer(), IMG_LoadTexture(renderer->getRenderer(), "res/block.png"), NULL, &copy);
            }
            
            if(CollisionHandler::intersects(&playerBB, bb))
                std::cout << "COLLIDING" << std::endl;
            //else
            //    std::cout << "No Collision" << std::endl;
		}
    }
    //SDL_RenderClear(renderer->getRenderer());
    /*std::pair<Chunk*, Vec2> chunkPair = getChunk(player->getPosition());
    
	Chunk* currChunk = chunkPair.first;
    Vec2 chunkVec2 = chunkPair.second;
    
	if(currChunk != nullptr)
	{
        std::pair<Tile*, Vec2> tilePair = getTile(currChunk->getTiles(), player->getPosition());
        
        Tile* currTile = tilePair.first;
        Vec2 tileVec2 = tilePair.second;
        
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
                //bb->x = (chunkVec2.x)*ChunkSize + (tileVec2.x+1)*TileSize;
                //bb->y = (chunkVec2.y)*ChunkSize + (tileVec2.y+1)*TileSize;
                
                SDL_Rect copy = *bb;
                
                copy.x = ((chunkVec2.x*3)+tileVec2.x)*copy.w + playerX;
                copy.y = ((chunkVec2.y*3)+tileVec2.y)*(copy.h) + playerY;
                
                bb->x = ((chunkVec2.x*3)+tileVec2.x)*bb->w;
                bb->y = ((chunkVec2.y*3)+tileVec2.y)*(bb->h);
                
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
	}*/
    //SDL_RenderPresent(renderer->getRenderer());
}

/*std::pair<Chunk*, Vec2> Game::getChunk(Vec2* Vec2)
{
	Vec2 c = Vec2((int)(Vec2->x/ChunkSize), (int)(((Vec2->y+200)/(ChunkSize/2))));
    //TODO Add support for multiple chunks for detection
	//std::cout << "Chunk X: " << c.x << " Chunk Y: " << c.y << std::endl;
	return std::make_pair(chunks[c], Vec2(c.x, c.y));
}

std::pair<Tile*, Vec2> Game::getTile(std::HashMap<Vec2, Tile*> tiles, Vec2* Vec2)
{
	Vec2 c = Vec2((int)((int)Vec2->x%ChunkSize), (int)(((int)(Vec2->y+200)%(ChunkSize/2))));
    //TODO Add support for multiple tiles for detection
    c.x /= TileSize;
    c.y /= TileSize/2;
	//std::cout << "Tile X: " << c.x << " Tile Y: " << c.y << std::endl;
	return std::make_pair(tiles[c], Vec2(c.x, c.y));
}*/

std::vector<std::pair<Tile*, Vec2> > Game::getSurroundingTiles(int radius, Vec2* centerPos)
{
    std::vector<std::pair<Tile*, Vec2> > t;
    
    Vec2 centerPosInChunk = centerPos->inChunkVec2();
    Vec2 centerPosInTile = centerPos->inTileVec2();
    /* int centerTilePosX = centerPos->x/TileSize;
    int centerTilePosY = centerPos->y/(TileSize/2);
    
    Vec2 chunkVec2 = Vec2((int)(centerPos->x/ChunkSize), (int)((centerPos->y/(ChunkSize/2))));
    
    std::cout << "centerX: " << centerTilePosX << " centerY: " << centerTilePosY << std::endl;
    std::cout << "centerChunkX: " << chunkVec2.x << " centerChunkY: " << chunkVec2.y << std::endl;*/
    
    
    std::vector<Chunk*> c;
    c.push_back(chunks[Vec2(centerPosInChunk.x, centerPosInChunk.y)]);
    
    
    
    for (int x = centerPosInTile.x - radius; x <= centerPosInTile.x + radius; x++)
    {
        for (int y = centerPosInTile.y - radius; y <= centerPosInTile.y + radius; y++)
        {
            
            if(centerPosInChunk == *c[0]->getCoord())
            {
                Vec2 tileCoord = Vec2((int)((int)x%ChunkSize), (int)(((int)y%(ChunkSize/2))));
                
                t.push_back(std::make_pair(c[0]->getTiles()[tileCoord], Vec2(tileCoord.x, tileCoord.y)));
            }
            //else
            //    std::cout << "NEED TO LOAD ANOTHER CHUNK TO GET TILES: " << chunkVec2.x << " Y: " << chunkVec2.y << std::endl;
                //TODO LOAD OTHER CHUNKS
            //std::cout << "X: " << x << " Y: " << y << std::endl;
        }
    }
    //v.push_back(std::make_pair(currTile, Vec2()));
    //TODO Push back tiles that are inside of radius (need to search through chunks)
    return t;
}