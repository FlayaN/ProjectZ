#include "Renderer.h"


Renderer::Renderer(SDL_Window* win) {
	this->win = win;
	renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

Renderer::~Renderer(void) {

}

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, SDL_Rect dst) {
	SDL_RenderCopy(ren, tex, NULL, &dst);
}

void Renderer::render(Tile* tiles[10][10], EntityPlayer* player) {

	int w,h;
	SDL_GetWindowSize(win, &w, &h);

	float playerX = -player->getPosition()->x;
	float playerY = player->getPosition()->y;

	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xff);
	SDL_RenderClear(renderer);
	
	SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);

	int tileSize = 100;

	for(int x = 0; x < w; x+=tileSize) {
		SDL_RenderDrawLine(renderer, x+playerX, 0, x+playerX, h);
		for(int y = 0; y < h; y+=tileSize/2) {
			SDL_RenderDrawLine(renderer, 0, y+playerY, w, y+playerY);
		}
	}
    
    SDL_Rect dst;
    dst.w = tileSize;
    dst.h = tileSize/2;
    
	for(int x = 0; x < 10; x++) {
		for(int y = 0; y < 10; y++) {

			if(tiles[x][y] != nullptr) {
				SDL_Texture* tex = tiles[x][y]->getTexture();
			
				dst.x = x*dst.w+playerX;
				dst.y = y*dst.h+playerY;
				renderTexture(tex, renderer, dst);
			}
		}
	}

	SDL_Rect rect = *player->getRect();
	rect.x = w/2 - rect.w/2;
	rect.y = h/2 - rect.h/2;

	renderTexture(player->getTexture(), renderer, rect);

    SDL_RenderPresent(renderer);
}

SDL_Renderer* Renderer::getRenderer() {
	return renderer;
}