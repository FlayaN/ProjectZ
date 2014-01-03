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
    int totAwayFromOrigin = std::max(abs(coord->x), abs(coord->y));
    totAwayFromOrigin *= 5;
    
    int r = Utility::clamp(Utility::getRandInt(250, 255)-totAwayFromOrigin, 0, 255);
    int g = Utility::clamp(Utility::getRandInt(250, 255)-totAwayFromOrigin, 0, 255);
    int b = Utility::clamp(Utility::getRandInt(250, 255)-totAwayFromOrigin, 0, 255);
    
    Vec3* colorMod = new Vec3(r, g, b);
    
	for(int x = 0; x < TileAmount; x++)
	{
		for(int y = 0; y < TileAmount; y++)
		{
			tiles[x][y] = new Tile(s, new Vec2(TileAmount*coord->x+x, TileAmount*coord->y+y), colorMod);
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