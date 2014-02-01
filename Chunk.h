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
#include "GroundItem.h"
#include "TypeMaterial.h"

class Chunk
{
public:
	Chunk(glm::ivec2 coord, std::vector<TypeTile>, std::vector<std::shared_ptr<TypeItem> >);
	~Chunk(void);

	std::shared_ptr<Tile> getTile(const glm::ivec2& pos);
	std::vector<std::shared_ptr<GroundItem> > getGroundItems(void);
	void addGroundItem(std::shared_ptr<GroundItem>);
	void removeGroundItem(int id, glm::vec2 pos);

    glm::ivec2 getCoord(void);

private:

	std::shared_ptr<Tile> tiles[TileAmount][TileAmount];
	std::vector<std::shared_ptr<GroundItem> > groundItems;
    glm::ivec2 coord;
};

#endif