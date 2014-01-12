#include "Chunk.h"

Chunk::Chunk(glm::ivec2* coord) : coord(coord)
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
			std::cout << PerlinNoise::getInstance().GetHeight(TileAmount*coord->x+x, TileAmount*coord->y+y);
			tiles[x][y] = new Tile(s, new glm::vec2(TileAmount*coord->x+x, TileAmount*coord->y+y));
		}
	}
}

Tile* Chunk::getTile(const glm::ivec2& pos)
{
	return tiles[pos.x][pos.y];
}

glm::ivec2* Chunk::getCoord(void)
{
	return coord;
}