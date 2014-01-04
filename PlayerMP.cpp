#include "PlayerMP.h"

PlayerMP::PlayerMP(int idIn) : id(idIn), Entity()
{
	size = new SDL_Rect();
	size->w = TileWidth;
	size->h = TileWidth*2;
}

SDL_Rect* PlayerMP::getSize(void)
{
	return size;
}

int PlayerMP::getId(void)
{
	return id;
}