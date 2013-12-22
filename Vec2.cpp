#include "Vec2.h"

Vec2::Vec2(float xIn, float yIn)
{
	x = xIn;
	y = yIn;
}

Vec2::~Vec2(void)
{

}

Vec2 Vec2::inTileCoord(void)
{
	Vec2 tmp = Vec2(x, y);
	tmp.x = x >= 0 ? (x/TileWidth) : (x/TileWidth)-1;
	tmp.y = y >= 0 ? (y/TileHeight) : (y/TileHeight)-1;
	return Vec2((int)tmp.x, (int)tmp.y);
}

Vec2 Vec2::inChunkCoord(void)
{
	Vec2 tmp = Vec2(x, y);
	tmp.x = x >= 0 ? (x/ChunkWidth) : (x/ChunkWidth)-1;
	tmp.y = y >= 0 ? (y/ChunkHeight) : (y/ChunkHeight)-1;
	return Vec2((int)tmp.x, (int)tmp.y);
}

Vec2 Vec2::withinRange(void)
{
	return Vec2(Utility::mod(x, TileAmount), Utility::mod(y, TileAmount));
}