#include "Utility.h"

int Utility::getRandInt(int min, int max)
{
	std::random_device rd;
	std::uniform_int_distribution<int> distribution(min, max);

	return distribution(rd);
}

int Utility::clamp(int value, int min, int max)
{
	return std::min(max, std::max(min, value));
}

int Utility::mod(int v, int m)
{
	int r = v% m;
	return r<0 ? r+m : r;
}

glm::ivec2 Utility::inTileCoord(glm::vec2 inPos)
{
	inPos.x = inPos.x >= 0 ? (inPos.x/Settings::Tile::width) : (inPos.x/Settings::Tile::width)-1;
	inPos.y = inPos.y >= 0 ? (inPos.y/Settings::Tile::height) : (inPos.y/Settings::Tile::height)-1;
	return (glm::ivec2)inPos;
}

glm::ivec2 Utility::inChunkCoord(glm::vec2 inPos)
{
	inPos.x = inPos.x >= 0 ? (inPos.x/ChunkWidth) : (inPos.x/ChunkWidth)-1;
	inPos.y = inPos.y >= 0 ? (inPos.y/ChunkHeight) : (inPos.y/ChunkHeight)-1;
	return (glm::ivec2)inPos;
}

glm::ivec2 Utility::withinRange(glm::ivec2 inPos)
{
	return glm::ivec2(Utility::mod(inPos.x, TileAmount), Utility::mod(inPos.y, TileAmount));
}