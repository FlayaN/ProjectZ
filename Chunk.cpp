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
    int totAwayFromOrigin = std::max(abs(coord->x), abs(coord->y));
    totAwayFromOrigin *= 5;
    
    int r = Utility::clamp(Utility::getRandInt(250, 255)-totAwayFromOrigin, 0, 255);
    int g = Utility::clamp(Utility::getRandInt(250, 255)-totAwayFromOrigin, 0, 255);
    int b = Utility::clamp(Utility::getRandInt(250, 255)-totAwayFromOrigin, 0, 255);
    
    glm::vec3* colorMod = new glm::vec3(r, g, b);
    
	for(int x = 0; x < TileAmount; x++)
	{
		for(int y = 0; y < TileAmount; y++)
		{
			tiles[x][y] = new Tile(s, new glm::vec2(TileAmount*coord->x+x, TileAmount*coord->y+y), colorMod);
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