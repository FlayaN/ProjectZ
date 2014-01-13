#include "Chunk.h"

Chunk::Chunk(glm::ivec2* coord, std::vector<TypeTile> tileTypes) : coord(coord)
{
	for(int x = 0; x < TileAmount; x++)
	{
		for(int y = 0; y < TileAmount; y++)
		{
			//std::cout << PerlinNoise::getInstance().GetHeight(TileAmount*coord->x+x, TileAmount*coord->y+y) << std::endl;
			int i = Utility::getRandInt(0, tileTypes.size()-1);
			tiles[x][y] = new Tile(i, tileTypes[i].friction, new glm::ivec2(TileAmount*coord->x+x, TileAmount*coord->y+y));
		}
	}
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

Tile* Chunk::getTile(const glm::ivec2& pos)
{
	return tiles[pos.x][pos.y];
}

glm::ivec2* Chunk::getCoord(void)
{
	return coord;
}