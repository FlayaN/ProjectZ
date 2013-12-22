#include "ChunkUtility.h"

std::vector<Tile*> ChunkUtility::getSurroundingTiles(std::HashMap<Vec2, Chunk*> chunks, int radius, Vec2* centerPos)
{
	std::vector<Tile*> t;
	Vec2 centerPosInChunk = centerPos->inChunkCoord();
	Vec2 centerPosInTile = centerPos->inTileCoord();
	//std::cout << " X: " << centerPosInTile.x << " Y: " << centerPosInTile.y << std::endl;
	//std::vector<Chunk*> c;
	//c.push_back(chunks[centerPosInChunk]);
	
	for (int x = centerPosInTile.x - radius; x <= centerPosInTile.x + radius; x++)
	{
		for (int y = centerPosInTile.y - radius; y <= centerPosInTile.y + radius; y++)
		{
			Vec2 chunkCoord = Vec2(x, y);
			//chunkCoord.x = chunkCoord.x >= 0 ? (int)chunkCoord.x/TileAmount : (int)(chunkCoord.x/TileAmount)-1;
			//chunkCoord.y = chunkCoord.y >= 0 ? (int)chunkCoord.y/TileAmount : (int)(chunkCoord.y/TileAmount)-1;
			
			chunkCoord.x = floor(chunkCoord.x/TileAmount);
			chunkCoord.y = floor(chunkCoord.y/TileAmount);

			//Vec2 tileCoord = Vec2(x, );

			Tile* tmpTile = chunks[chunkCoord]->getTile(Vec2(x, y).withinRange());
			if(tmpTile != nullptr)
			{
					//std::cout << "FROM TILE X: " << tmpTile->getCoord()->x << " Y: " << tmpTile->getCoord()->y << std::endl;
				t.push_back(tmpTile);
			}



			/*if(centerPosInChunk == *c[0]->getCoord())
			{
				
				Vec2 tileCoord = Vec2(x, y);//Vec2((int)((int)x%ChunkWidth), (int)(((int)y%ChunkHeight)));
				//std::cout << tileCoord;
				
				Tile* tmpTile = c[0]->getTile(tileCoord);
				if(tmpTile != nullptr)
				{
					//std::cout << "FROM TILE X: " << tmpTile->getCoord()->x << " Y: " << tmpTile->getCoord()->y << std::endl;
					t.push_back(tmpTile);
				}/*else
				{
					//TODO OPTIMIZE THIS A LOT!! VERY NEEDY

					//std::cout << "2NEED TO LOAD ANOTHER CHUNK TO GET TILES: X:" << x << " Y: " << y << std::endl;
					Vec2 tmpChunkPos = Vec2(x, y);
					tmpChunkPos.x = tmpChunkPos.x >= 0 ? (int)tmpChunkPos.x/TileAmount : (int)(tmpChunkPos.x/TileAmount)-1;
					tmpChunkPos.y = tmpChunkPos.y >= 0 ? (int)tmpChunkPos.y/TileAmount : (int)(tmpChunkPos.y/TileAmount)-1;
					
					//std::cout << "Chunk: X:" << tmpChunkPos.x << " Y: " << tmpChunkPos.y << std::endl;
					//Vec2 tmpTilePos = Vec2(x, y);
					//std::cout << "Tile: X:" << tmpTilePos.x << " Y: " << tmpTilePos.y << std::endl;

					//Chunk* tmpChunk = chunks[tmpChunkPos];


					Tile* tmpTile2 = chunks[tmpChunkPos]->getTile(tileCoord);

					if(tmpTile2 != nullptr)
					{
						t.push_back(tmpTile2);
					}
					else
						std::cout << "TILE ERROR" << std::endl;
					
					//std::cout << "2NEED TO LOAD ANOTHER CHUNK TO GET TILES: X:" << x << " Y: " << y << std::endl;
					/*std::vector<Tile*> tmps = getSurroundingTiles(chunks, radius-1, new Vec2(x*TileWidth, y*TileHeight));

					for(auto tmp: tmps)
					{
						t.push_back(tmp);
					}
				}*/

				/*if(Utility::isVec2InRange(tileCoord%TileAmount, 0, TileAmount))
				{
					
				}
			}
            else
				std::cout << "NEED TO LOAD ANOTHER CHUNK TO GET TILES: " << std::endl;
                //TODO LOAD OTHER CHUNKS
            //std::cout << "X: " << x << " Y: " << y << std::endl;
			*/
		}
	}
    //v.push_back(std::make_pair(currTile, Vec2()));
    //TODO Push back tiles that are inside of radius (need to search through chunks)
	return t;
}