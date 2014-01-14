#ifndef CHUNKUTILITY_H
#define CHUNKUTILITY_H

#include <math.h>
#include <sstream>

#include "Chunk.h"
#include "Utility.h"
#include "EntityPlayer.h"
#include "TypeTile.h"

namespace ChunkUtility
{
	std::vector<Tile*> getSurroundingTiles(std::HashMap<glm::ivec2, Chunk*> chunks, int radius, EntityPlayer);
	void generateSurroundingChunk(std::HashMap<glm::ivec2, Chunk*>& chunks, int radius, EntityPlayer, std::vector<TypeTile>);
};

namespace std
{
	template <>
	struct hash<glm::ivec2>
	{
		std::size_t operator()(const glm::ivec2& k) const
		{
			return ((hash<int>()(k.x) ^ (hash<int>()(k.y) << 1)));
		}
	};
}

#endif