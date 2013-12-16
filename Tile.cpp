#include "Tile.h"

//using namespace std;

void logSDLError(std::ostream &os, const std::string &msg){
	os << msg << " error: " << SDL_GetError() << std::endl;
}

Tile::Tile(Vec3* positionIn, Shape* northAreaIn, Shape* southAreaIn, Shape* westAreaIn, Shape* eastAreaIn)
{
	position = positionIn;
	northArea = northAreaIn;
	southArea = southAreaIn;
	westArea = westAreaIn;
	eastArea = eastAreaIn;
}

Tile::Tile(SDL_Renderer* ren, std::string s)
{
	bb = new SDL_Rect();
	bb->h = TileSize/2;
	bb->w = TileSize;
	if(Utility::getRandInt(1, 10) < 3)
	{
		tex = IMG_LoadTexture(ren, "res/block.png");
		/*bb = new SDL_Rect();
		bb->h = 100;
		bb->w = 200;*/
	}
	else
	{
		tex = IMG_LoadTexture(ren, s.c_str());
		//bb = nullptr;
	}
}

Tile::~Tile(void)
{
	delete position;
	delete northArea;
	delete southArea;
	delete westArea;
	delete eastArea;
}

SDL_Texture* Tile::getTexture(void)
{
    return tex;
}

SDL_Rect* Tile::getBB(void)
{
	return bb;
}