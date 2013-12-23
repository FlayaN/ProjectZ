#pragma once

#include <math.h>
#include <sstream>

#include "Chunk.h"
#include "Utility.h"
#include "EntityPlayer.h"

#ifndef CHUNKUTILITY_H
#define CHUNKUTILITY_H

namespace ChunkUtility
{
	std::vector<Tile*> getSurroundingTiles(std::HashMap<Vec2, Chunk*> chunks, int radius, EntityPlayer* centerPos);
	std::HashMap<Vec2, Chunk*> generateSurroundingChunk(std::HashMap<Vec2, Chunk*> chunks, int radius, Vec2* centerPos);
};

#endif