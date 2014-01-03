#pragma once

#include <unordered_map>
#include <string>
#include <assert.h>
#include <stdlib.h>
#include <algorithm>

#include "Defines.h"
#include "Tile.h"


#ifndef CHUNK_H
#define CHUNK_H

class Chunk
{
public:
	Chunk(Vec2* coord);
	~Chunk(void);

	void init(std::string);
	
	Tile* getTile(const Vec2& pos);

    Vec2* getCoord(void);

private:

	Tile* tiles[TileAmount][TileAmount];
    Vec2* coord;
};

#endif