#include "Vec2.h"

Vec2::Vec2(float xIn, float yIn)
{
	x = xIn;
	y = yIn;
}

Vec2::~Vec2(void)
{

}

Vec2 Vec2::inTileVec2(void)
{
    return Vec2((int)(x/TileSize), (int)(y/(TileSize/2)));
}

Vec2 Vec2::inChunkVec2(void)
{
    return Vec2((int)(x/ChunkSize), (int)(y/(ChunkSize/2)));
}