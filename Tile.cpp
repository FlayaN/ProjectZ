#include "Tile.h"

using namespace std;

void logSDLError(std::ostream &os, const std::string &msg){
	os << msg << " error: " << SDL_GetError() << std::endl;
}

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
	tex = IMG_LoadTexture(ren, "res/grass.png");
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