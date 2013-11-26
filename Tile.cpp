#include "Tile.h"


Tile::Tile(Position* positionIn, Area* northAreaIn, Area* southAreaIn, Area* westAreaIn, Area* eastAreaIn)
{
	position = positionIn;
	northArea = northAreaIn;
	southArea = southAreaIn;
	westArea = westAreaIn;
	eastArea = eastAreaIn;
}

Tile::Tile(SDL_Renderer* ren)
{
	//texture = SDL_
    //surface = IMG_Load("grass.png");
    tex = IMG_LoadTexture(ren, "grass.png");
    if (tex == nullptr)
		std::cout << "LoadTexture";
    /*if (surface != nullptr){
		tex = SDL_CreateTextureFromSurface(ren, surface);
		SDL_FreeSurface(surface);
		//Make sure converting went ok too
		//if (tex == nullptr)
			//logSDLError(std::cout, "CreateTextureFromSurface");
	}*/
}

Tile::~Tile(void)
{
	delete position;
	delete northArea;
	delete southArea;
	delete westArea;
	delete eastArea;
}

SDL_Texture* Tile::getTexture() {
    return tex;
}
