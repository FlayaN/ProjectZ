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
	for(int i = 0; i < 9; i++)
	{
		tiles[i] = new Tile(renderer, s);
	}

	//tiles[31] = new Tile(renderer->getRenderer()); //Add a tile here to tiles to render it
}

HashMap<int, Tile*> Chunk::getTiles(void)
{
	return tiles;
}