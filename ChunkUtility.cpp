#include "ChunkUtility.h"

std::vector<std::shared_ptr<Tile> > ChunkUtility::getSurroundingTiles(std::HashMap<glm::ivec2, std::shared_ptr<Chunk> > chunks, int radius, EntityPlayer player)
{
	glm::vec2 centerPos = player.getCenterPosition();
	std::vector<std::shared_ptr<Tile> > t;
	glm::ivec2 centerPosInChunk = Utility::inChunkCoord(centerPos);
	glm::ivec2 centerPosInTile = Utility::inTileCoord(centerPos);

	for(int x = centerPosInTile.x - radius; x <= centerPosInTile.x + radius; x++)
	{
		for(int y = centerPosInTile.y - radius; y <= centerPosInTile.y + radius; y++)
		{
			glm::ivec2 chunkCoord(floor((float)x/TileAmount), floor((float)y/TileAmount));

			std::shared_ptr<Chunk> tmpChunk = chunks[chunkCoord];
			
			if(tmpChunk != nullptr)
			{
				std::shared_ptr<Tile> tmpTile = tmpChunk->getTile(Utility::withinRange(glm::ivec2(x, y)));

				if(&tmpTile != nullptr)
				{
					t.push_back(tmpTile);
				}
			}
		}
	}

	return t;
}

std::vector<std::shared_ptr<GroundItemStack> > ChunkUtility::getSurroundingItems(std::HashMap<glm::ivec2, std::shared_ptr<Chunk> > chunks, EntityPlayer player)
{
	std::vector<std::shared_ptr<GroundItemStack> > t;

	glm::ivec2 centerPosInChunk = Utility::inChunkCoord(player.getCenterPosition());

	for(int x = centerPosInChunk.x - 2; x <= centerPosInChunk.x + 2; x++)
	{
		for(int y = centerPosInChunk.y - 2; y <= centerPosInChunk.y + 2; y++)
		{
			std::shared_ptr<Chunk> tmpChunk = chunks[glm::ivec2(x, y)];
			
			if(tmpChunk != nullptr)
			{
				std::vector<std::shared_ptr<GroundItemStack> > t2 = tmpChunk->getGroundItemStacks();
				t.insert(t.end(), t2.begin(), t2.end());
			}
		}
	}

	return t;
}

void ChunkUtility::generateSurroundingChunk(std::HashMap<glm::ivec2, std::shared_ptr<Chunk> >& chunks, int radius, EntityPlayer player, std::vector<std::shared_ptr<TypeTile> > tileTypes, std::vector<std::shared_ptr<TypeItem> > itemTypes)
{
	glm::ivec2 centerPosInChunk = Utility::inChunkCoord(player.getCenterPosition());

	std::HashMap<glm::ivec2,std::shared_ptr<Chunk> > newchunks;
	std::HashMap<glm::ivec2, bool> checker;

	for (int x = centerPosInChunk.x - radius; x <= centerPosInChunk.x + radius; x++)
	{
		for (int y = centerPosInChunk.y - radius; y <= centerPosInChunk.y + radius; y++)
		{
			if(chunks[glm::ivec2(x, y)] != nullptr)
			{
				newchunks[glm::ivec2(x, y)] = chunks[glm::ivec2(x, y)];
				checker[glm::ivec2(x, y)] = true;
			}
			else
			{
				newchunks[glm::ivec2(x, y)] = std::make_shared<Chunk>(glm::ivec2(x, y), tileTypes, itemTypes);
				checker[glm::ivec2(x, y)] = true;
			}
		}
	}

	for(auto it = chunks.begin(); it != chunks.end();)
	{
		if(!checker[it->first])
			it = chunks.erase(it);
		else
			it++;
	}

	chunks = newchunks;
}