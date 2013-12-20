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
	for(int x = coord->x*TileAmount; x < (coord->x*TileAmount)+TileAmount; x++)
	{
		for(int y = coord->y*TileAmount; y < (coord->y*TileAmount)+TileAmount; y++)
		{
			//std::cout << "CHUNK X " << coord->x << " Y: " << coord->y << std::endl;
			//std::cout << "Tile X " << x << " Y: " << y << std::endl;
			tiles[Vec2(x, y)] = new Tile(renderer, s, new Vec2(x, y));
		}
	}
}

std::HashMap<Vec2, Tile*> Chunk::getTiles(void)
{
	return tiles;
}

Vec2* Chunk::getCoord(void)
{
	return coord;
}