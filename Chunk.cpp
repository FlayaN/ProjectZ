#include "Chunk.h"

Chunk::Chunk(Vec2* coord) : coord(coord)
{
	//init(renderer);
}

Chunk::~Chunk(void)
{
	for (int x = 0; x < TileAmount; x++)
    {
        for (int y = 0; y < TileAmount; y++)
        {
            delete tiles[x][y];
        }
    }
	delete coord;
}

void Chunk::init(std::string s)
{
	for(int x = 0; x < TileAmount; x++)
	{
		for(int y = 0; y < TileAmount; y++)
		{
			tiles[x][y] = new Tile(s, new Vec2(TileAmount*coord->x+x, TileAmount*coord->y+y));
		}
	}
}

Tile* Chunk::getTile(const Vec2& pos)
{
	return tiles[(int)pos.x][(int)pos.y];
}

Vec2* Chunk::getCoord(void)
{
	return coord;
}