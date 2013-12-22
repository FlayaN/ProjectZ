#pragma once


#include <unordered_map>
#include <string>
#include <assert.h>

#include "Defines.h"
#include "Tile.h"

class Chunk
{
public:
	Chunk(Vec2* coord);
	~Chunk(void);

	void init(SDL_Renderer*, std::string);
	
    //std::HashMap<Vec2, Tile*> getTiles(void);
    //Tile** getTiles(void);
	Tile* getTile(const Vec2& pos);

    Vec2* getCoord(void);

private:
    //std::HashMap<Vec2, Tile*> tiles;
	Tile* tiles[TileAmount][TileAmount];

    Vec2* coord;
};