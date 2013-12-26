#include "ChunkUtility.h"

std::vector<Tile*> ChunkUtility::getSurroundingTiles(std::HashMap<Vec2, Chunk*> chunks, int radiusIn, EntityPlayer* player)
{
	int radius = radiusIn+1; //Need to increment by one for some reason

	Vec2 centerPos = player->getCenterPosition();
	std::vector<Tile*> t;
	Vec2 centerPosInChunk = centerPos.inChunkCoord();
	Vec2 centerPosInTile = centerPos.inTileCoord();
	int diameter = radius*2;

	for (int x = 0; x <= diameter; x++)
	{
		for (int y = 0; y <= diameter; y++)
		{
			if((x-radius)*(x-radius)+(y-radius)*(y-radius) < radius*radius)
			{
				Vec2 offset = Vec2(centerPosInTile.x+(x-radius), centerPosInTile.y+(y-radius));

				Vec2 chunkCoord = offset;
				chunkCoord.x = floor(chunkCoord.x/TileAmount);
				chunkCoord.y = floor(chunkCoord.y/TileAmount);

				Chunk* tmpChunk = chunks[chunkCoord];

				if(tmpChunk != nullptr)
				{
					Tile* tmpTile = tmpChunk->getTile(offset.withinRange());

					if(tmpTile != nullptr)
					{
						t.push_back(tmpTile);
					}
				}
			}
		}
	}

	return t;
}

std::HashMap<Vec2, Chunk*> ChunkUtility::generateSurroundingChunk(std::HashMap<Vec2, Chunk*> chunks, int radius, EntityPlayer* player)
{
	Vec2 centerPosInChunk = player->getCenterPosition().inChunkCoord();

	std::HashMap<Vec2, Chunk*> newchunks;

	for (int x = centerPosInChunk.x - radius; x <= centerPosInChunk.x + radius; x++)
	{
		for (int y = centerPosInChunk.y - radius; y <= centerPosInChunk.y + radius; y++)
		{
			if(chunks[Vec2(x, y)] != nullptr)
				newchunks[Vec2(x, y)] = chunks[Vec2(x, y)];
			else
			{
				Chunk* chunk = new Chunk(new Vec2(x, y));

				chunk->init(std::to_string(Utility::getRandInt(1, 9)));
				newchunks[Vec2(x, y)] = chunk;
			}
		}
	}
	return newchunks;
}