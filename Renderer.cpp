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

void Renderer::render(std::HashMap<Vec2, Chunk*> chunks, EntityPlayer* player, std::vector<PlayerMP*> players)
{
	SDL_Renderer* renderer = Graphics::getInstance().getRenderer();
	SDL_GetWindowSize(Graphics::getInstance().getWindow(), &w, &h);
	//Vec2 playerOffset = Vec2(-player->getCenterPosition().x + w/2, -player->getCenterPosition().y + h/2);

	//BG COLOR
	SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);

	//CLEAR SCREEN
	SDL_RenderClear(renderer);
    
	renderTile(chunks, player);
	renderGrid(player);
	renderEntity(player, players);

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
            
            Vec3* tmpColorMod = tile->getColorMod();
            SDL_SetTextureColorMod(tex, tmpColorMod->x, tmpColorMod->y, tmpColorMod->z);
            
			renderTexture(tex, dst);
		}
	}
}

void Renderer::renderGrid(EntityPlayer* player)
{
	Vec2 playerOffset = Vec2(-player->getCenterPosition().x + w/2, -player->getCenterPosition().y + h/2);

	SDL_Renderer* renderer = Graphics::getInstance().getRenderer();

	for(int x = player->getPosition()->x-w; x < player->getPosition()->x+w; x+=TileWidth)
	{
		int tmpX = x-(x%TileWidth);
		

		SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0xff);
		if(tmpX%(TileAmount*TileWidth) == 0)
			SDL_SetRenderDrawColor(renderer, 0xff, 0x0, 0x0, 0xff);	

		SDL_RenderDrawLine(renderer, tmpX+playerOffset.x, 0, tmpX+playerOffset.x, h);
		
		for(int y = player->getPosition()->y-h; y < player->getPosition()->y+h; y+=TileHeight)
		{

			int tmpY = y-(y%TileHeight);
			
			SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0xff);
			if(tmpY%(TileAmount*TileHeight) == 0)
				SDL_SetRenderDrawColor(renderer, 0xff, 0x0, 0x0, 0xff);	

			SDL_RenderDrawLine(renderer, 0, tmpY+playerOffset.y, w, tmpY+playerOffset.y);
		}
	}
}

void Renderer::renderEntity(EntityPlayer* player, std::vector<PlayerMP*> players)
{

	//Player
	SDL_Rect playerCollisionBox = *player->getBB();
	playerCollisionBox.x = w/2 - playerCollisionBox.w/2;
	playerCollisionBox.y = h/2 - playerCollisionBox.h/2;

	renderTexture(player->getCollisionTexture(), playerCollisionBox);

	SDL_Rect playerRect = *player->getSize();
	playerRect.x = w/2 - playerRect.w/2;
	playerRect.y = h/2 - (playerRect.h - playerCollisionBox.h/2);
    
    renderTexture(player->getTexture(), playerRect);


	//MP STUFF

	Vec2 playerOffset = Vec2(-player->getCenterPosition().x + w/2, -player->getCenterPosition().y + h/2);

	for(auto p : players)
	{
		
		SDL_Rect pRect = *p->getSize();
		pRect.x = p->getPosition()->x + playerOffset.x;
		pRect.y = p->getPosition()->y + playerOffset.y - pRect.h/2 - pRect.h/4;

		renderTexture(player->getTexture(), pRect);
	}
}