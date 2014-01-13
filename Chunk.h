#ifndef CHUNK_H
#define CHUNK_H

#include <unordered_map>
#include <string>
#include <assert.h>
#include <stdlib.h>
#include <algorithm>

#include "Defines.h"
#include "Tile.h"
#include "PerlinNoise.h"
#include "TypeTile.h"

class Chunk
{
public:
	Chunk(glm::ivec2* coord, std::vector<TypeTile>);
	~Chunk(void);

	Tile* getTile(const glm::ivec2& pos);

    glm::ivec2* getCoord(void);

private:

	Tile* tiles[TileAmount][TileAmount];
    glm::ivec2* coord;
};

#endif