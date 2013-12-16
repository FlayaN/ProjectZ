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

void Renderer::render(std::HashMap<Coord, Chunk*> chunks, EntityPlayer* player)
{

	int w,h;
	SDL_GetWindowSize(win, &w, &h);

	float playerX = -player->getPosition()->x;
	float playerY = player->getPosition()->y;

	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xff);
	SDL_RenderClear(renderer);
	
	SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
	
	SDL_Rect dst;
	dst.w = TileSize;
	dst.h = TileSize/2;

	int size = 3;

	for(std::HashMap<Coord, Chunk*>::const_iterator i = chunks.begin(), e = chunks.end(); i != e ; ++i )
	{
		Chunk* currChunk = i->second;
		if(currChunk != nullptr)
		{
			std::HashMap<Coord, Tile*> tiles = currChunk->getTiles();

			int chunkPosX = i->first.x;
			int chunkPosY = i->first.y;
			for(std::HashMap<Coord, Tile*>::const_iterator j = tiles.begin(), f = tiles.end(); j != f ; ++j )
			{
				Tile* tile = j->second;
				int x = j->first.x;
				int y = j->first.y;

				if(tile != nullptr)
				{
					SDL_Texture* tex = tile->getTexture();

					dst.x = ((chunkPosX*size)+x)*dst.w + playerX;
					dst.y = ((chunkPosY*size)+y)*dst.h + playerY;

					renderTexture(tex, renderer, dst);
				}
			}
		}
	}

	for(int x = 0; x < w*10; x+=TileSize)
	{
		SDL_RenderDrawLine(renderer, x+playerX, 0, x+playerX, h);
		for(int y = 0; y < h*10; y+=TileSize/2)
		{
			SDL_RenderDrawLine(renderer, 0, y+playerY, w, y+playerY);
		}
	}

	SDL_Rect rect = *player->getSize();
	rect.x = w/2 - rect.w/2;
	rect.y = h/2 - rect.h/2;
	renderTexture(player->getTexture(), renderer, rect);

    SDL_RenderPresent(renderer);
}

SDL_Renderer* Renderer::getRenderer()
{
	return renderer;
}