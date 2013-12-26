#include "Tile.h"

//using namespace std;

void logSDLError(std::ostream &os, const std::string &msg){
	os << msg << " error: " << SDL_GetError() << std::endl;
}

Tile::Tile(std::string s, Vec2* positionIn)
{
	/*bb = new SDL_Rect();
	bb->h = TileSize/2;
	bb->w = TileSize;*/
    position = positionIn;
    
	if(Utility::getRandInt(1, 10) < 3)
	{
		tex = TextureManager::getInstance().getTexture("block");
		bb = new SDL_Rect();
		bb->h = TileHeight;
		bb->w = TileWidth;
	}
	else
	{
		tex = TextureManager::getInstance().getTexture(s);
		bb = nullptr;
	}
}

Tile::~Tile(void)
{
}

SDL_Texture* Tile::getTexture(void)
{
	return tex;
}

SDL_Rect* Tile::getBB(void)
{
	return bb;
}

Vec2* Tile::getPosition(void)
{
	return position;
}