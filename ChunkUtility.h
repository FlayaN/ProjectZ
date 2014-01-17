#ifndef CHUNKUTILITY_H
#define CHUNKUTILITY_H

#include <math.h>
#include <sstream>
#include <memory>

#include "Chunk.h"
#include "Utility.h"
#include "EntityPlayer.h"

namespace ChunkUtility
{
	std::vector<std::shared_ptr<Tile> > getSurroundingTiles(std::HashMap<glm::ivec2, std::shared_ptr<Chunk> >, int, EntityPlayer);
	std::vector<std::shared_ptr<GroundItem> > getSurroundingItems(std::HashMap<glm::ivec2, std::shared_ptr<Chunk> >, EntityPlayer);
	void generateSurroundingChunk(std::HashMap<glm::ivec2, std::shared_ptr<Chunk> >&, int, EntityPlayer, std::vector<TypeTile>, std::vector<std::shared_ptr<TypeItem> >);
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