#include "Renderer.h"


Renderer::Renderer(SDL_Window* win)
{
	this->win = win;
	renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

Renderer::~Renderer(void) 
{

}

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, SDL_Rect dst)
{
	SDL_RenderCopy(ren, tex, NULL, &dst);
}

void Renderer::render(HashMap<int, Chunk*> chunks, EntityPlayer* player)
{

	int w,h;
	SDL_GetWindowSize(win, &w, &h);

	float playerX = -player->getPosition()->x;
	float playerY = player->getPosition()->y;

	//float playerChunkX = 
	//float playerChunkY = 

	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xff);
	SDL_RenderClear(renderer);
	
	SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);

	int tileSize = 500;
	
	SDL_Rect dst;
	dst.w = tileSize;
	dst.h = tileSize/2;

	int size = 3;

	for(HashMap<int, Chunk*>::const_iterator i = chunks.begin(), e = chunks.end(); i != e ; ++i )
	{
		Chunk* currChunk = i->second;
		HashMap<int, Tile*> tiles = currChunk->getTiles();

		int chunkPos = i->first;
		int chunkPosX = chunkPos/size;
		int chunkPosY = chunkPos%size;
		for(HashMap<int, Tile*>::const_iterator j = tiles.begin(), f = tiles.end(); j != f ; ++j )
		{
			Tile* tile = j->second;
			int coord = j->first;
			int x = coord/size;
			int y = coord%size;

			if(tile != nullptr)
			{
				SDL_Texture* tex = tile->getTexture();

				dst.x = ((chunkPosX*size)+x)*dst.w + playerX;
				dst.y = ((chunkPosY*size)+y)*dst.h + playerY;

				renderTexture(tex, renderer, dst);
			}
		}
	}

	for(int x = 0; x < w*10; x+=tileSize)
	{
		SDL_RenderDrawLine(renderer, x+playerX, 0, x+playerX, h);
		for(int y = 0; y < h*10; y+=tileSize/2)
		{
			SDL_RenderDrawLine(renderer, 0, y+playerY, w, y+playerY);
		}
	}

	SDL_Rect rect = *player->getRect();
	rect.x = w/2 - rect.w/2;
	rect.y = h/2 - rect.h/2;

	renderTexture(player->getTexture(), renderer, rect);

    SDL_RenderPresent(renderer);
}

SDL_Renderer* Renderer::getRenderer()
{
	return renderer;
}