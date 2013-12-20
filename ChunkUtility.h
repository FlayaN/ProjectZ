#pragma once

#include "Chunk.h"

#ifndef ChunkUtility_H
#define ChunkUtility_H

namespace ChunkUtility
{
	std::vector<std::pair<Tile*, Vec2> > getSurroundingTiles(std::HashMap<Vec2, Chunk*> chunks, int radius, Vec2* centerPos);
};

#endif