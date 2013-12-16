#pragma once


#include <unordered_map>
#include <string>

#include "Defines.h"
#include "Tile.h"
#include "Coord.h"

class Chunk
{
public:
	Chunk(void);
	~Chunk(void);

	void init(SDL_Renderer*, std::string);
	
    std::HashMap<Coord, Tile*> getTiles(void);

private:
    std::HashMap<Coord, Tile*> tiles;
};