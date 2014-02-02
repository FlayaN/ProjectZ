#ifndef CHUNK_H
#define CHUNK_H

#include <unordered_map>
#include <string>
#include <assert.h>
#include <stdlib.h>
#include <algorithm>
#include <memory>

#include "Defines.h"
#include "Tile.h"
#include "PerlinNoise.h"
#include "TypeTile.h"
#include "SimplexNoise.h"
#include "GroundItemStack.h"
#include "TypeMaterial.h"

class Chunk
{
public:
	Chunk(glm::ivec2 coord, std::vector<TypeTile>, std::vector<std::shared_ptr<TypeItem> >);
	~Chunk(void);

	std::shared_ptr<Tile> getTile(glm::ivec2);
	std::vector<std::shared_ptr<GroundItemStack> > getGroundItemStacks(void);
	void addGroundItem(std::shared_ptr<GroundItemStack>);
	void removeGroundItem(int, glm::vec2, int);

    glm::ivec2 getCoord(void);

private:

	std::shared_ptr<Tile> tiles[TileAmount][TileAmount];
	std::vector<std::shared_ptr<GroundItemStack> > groundItemStacks;
    glm::ivec2 coord;
};

#endif