#include "Chunk.h"

Chunk::Chunk(Vec2* coord) : coord(coord)
{
	//init(renderer);
}

Chunk::~Chunk(void)
{

}

void Chunk::init(SDL_Renderer* renderer, std::string s)
{
	for(int x = coord->x*3; x < (coord->x*3)+3; x++)
	{
		for(int y = coord->y*3; y < (coord->y*3)+3; y++)
		{
			tiles[Vec2(x, y)] = new Tile(renderer, s, new Vec2(x, y));
		}
	}
	/*
	for(int i = 0; i < 9; i++)
	{
		tiles[i] = new Tile(renderer, s);
	}*/

	//tiles[31] = new Tile(renderer->getRenderer()); //Add a tile here to tiles to render it
}

std::HashMap<Vec2, Tile*> Chunk::getTiles(void)
{
	return tiles;
}

Vec2* Chunk::getCoord(void)
{
    return coord;
}