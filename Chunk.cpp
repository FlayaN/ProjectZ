#include "Chunk.h"

Chunk::Chunk(void)
{
	//init(renderer);
}

Chunk::~Chunk(void)
{

}

void Chunk::init(SDL_Renderer* renderer, std::string s)
{
	for(int x = 0; x < 3; x++)
	{
		for(int y = 0; y < 3; y++)
		{
			tiles[Coord(x, y)] = new Tile(renderer, s);
		}
	}
	/*
	for(int i = 0; i < 9; i++)
	{
		tiles[i] = new Tile(renderer, s);
	}*/

	//tiles[31] = new Tile(renderer->getRenderer()); //Add a tile here to tiles to render it
}

std::HashMap<Coord, Tile*> Chunk::getTiles(void)
{
	return tiles;
}