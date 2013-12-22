#pragma once

#include "Chunk.h"
#include "Utility.h"

#include <math.h>

#ifndef ChunkUtility_H
#define ChunkUtility_H

namespace ChunkUtility
{
	std::vector<Tile*> getSurroundingTiles(std::HashMap<Vec2, Chunk*> chunks, int radius, Vec2* centerPos);
};

#endif