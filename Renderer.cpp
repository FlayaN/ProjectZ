#include "Renderer.h"


Renderer::Renderer(void)
{

}

Renderer::~Renderer(void) 
{

}

void renderTexture(SDL_Texture *tex, SDL_Rect dst)
{
	SDL_RenderCopy(Graphics::getInstance().getRenderer(), tex, NULL, &dst);
}

void Renderer::render(std::HashMap<Vec2, Chunk*> chunks, EntityPlayer* player)
{
	SDL_Renderer* renderer = Graphics::getInstance().getRenderer();
	SDL_GetWindowSize(Graphics::getInstance().getWindow(), &w, &h);
	Vec2 playerOffset = Vec2(-player->getCenterPosition().x + w/2, -player->getCenterPosition().y + h/2);

	//BG COLOR
	SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);

	//CLEAR SCREEN
	SDL_RenderClear(renderer);
	
	renderTile(chunks, player);
	//renderGrid(playerOffset);
	renderEntity(player);

	//SEND STUFF TO RENDERER
    SDL_RenderPresent(renderer);
}

void Renderer::renderTile(std::HashMap<Vec2, Chunk*> chunks, EntityPlayer* player)
{
	SDL_Rect dst;
	dst.w = TileWidth;
	dst.h = TileHeight;
	
	std::vector<Tile*> v = ChunkUtility::getSurroundingTiles(chunks, RenderDistance, player);

	Vec2 playerOffset = Vec2(-player->getCenterPosition().x + w/2, -player->getCenterPosition().y + h/2);

	for(Tile* tile: v)
	{
		if(tile != nullptr)
		{
			SDL_Texture* tex = tile->getTexture();
			dst.x = tile->getPosition()->x*dst.w + playerOffset.x;
			dst.y = tile->getPosition()->y*dst.h + playerOffset.y;
			renderTexture(tex, dst);
		}
	}
}

void Renderer::renderGrid(const Vec2& playerOffset)
{
	SDL_Renderer* renderer = Graphics::getInstance().getRenderer();

	SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0xff);

	for(int x = -w*2; x < w*2; x+=TileWidth)
	{
		SDL_RenderDrawLine(renderer, x+playerOffset.x, 0, x+playerOffset.x, h);
		for(int y = -h*2; y < h*2; y+=TileHeight)
		{
			SDL_RenderDrawLine(renderer, 0, y+playerOffset.y, w, y+playerOffset.y);
		}
	}
}

void Renderer::renderEntity(EntityPlayer* player)
{
	SDL_Rect playerCollisionBox = *player->getBB();
	playerCollisionBox.x = w/2 - playerCollisionBox.w/2;
	playerCollisionBox.y = h/2 - playerCollisionBox.h/2;

	renderTexture(player->getCollisionTexture(), playerCollisionBox);

	SDL_Rect playerRect = *player->getSize();
	playerRect.x = w/2 - playerRect.w/2;
	playerRect.y = h/2 - (playerRect.h - playerCollisionBox.h/2);
    
    renderTexture(player->getTexture(), playerRect);
}