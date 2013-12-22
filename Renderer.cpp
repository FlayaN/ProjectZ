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

void Renderer::render(std::HashMap<Vec2, Chunk*> chunks, EntityPlayer* player)
{
	int w,h;
	SDL_GetWindowSize(win, &w, &h);

	float playerX = -player->getPosition()->x + w/2 - player->getSize()->w/2;
	float playerY = -player->getPosition()->y + h/2 + player->getSize()->h/2;

	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
	
	SDL_Rect dst;
	dst.w = TileWidth;
	dst.h = TileHeight;
	
	std::vector<Tile*> v = ChunkUtility::getSurroundingTiles(chunks, RenderDistance, player->getPosition());

	for(Tile* tile: v)
	{
		if(tile != nullptr)
		{
			SDL_Texture* tex = tile->getTexture();
			dst.x = tile->getCoord()->x*dst.w + playerX;
			dst.y = tile->getCoord()->y*dst.h + playerY;
			
			//std::cout << "Player: " << *player->getPosition();

			//std::cout << "Tile: X;" << Vec2(tile->getCoord()->x*TileWidth, tile->getCoord()->y*TileHeight);

			renderTexture(tex, renderer, dst);
		}
	}
	SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0xff);

	for(int x = -w*2; x < w*2; x+=TileWidth)
	{
		SDL_RenderDrawLine(renderer, x+playerX, 0, x+playerX, h);
		for(int y = -h*2; y < h*2; y+=TileHeight)
		{
			SDL_RenderDrawLine(renderer, 0, y+playerY, w, y+playerY);
		}
	}

	SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);

	SDL_Rect playerCollisionBox = *player->getBB();
	playerCollisionBox.x = w/2 - playerCollisionBox.w/2;
	playerCollisionBox.y = h/2 + playerCollisionBox.h;

	renderTexture(player->getCollisionTexture(), renderer, playerCollisionBox);

	SDL_Rect playerRect = *player->getSize();
	playerRect.x = w/2 - playerRect.w/2;
	playerRect.y = h/2 - playerRect.h/2;
    
    renderTexture(player->getTexture(), renderer, playerRect);

	


    SDL_RenderPresent(renderer);
}

SDL_Renderer* Renderer::getRenderer()
{
	return renderer;
}