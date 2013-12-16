#pragma once


#include <unordered_map>
#include <string>

#include "Defines.h"
#include "Tile.h"

class Chunk
{
public:
	Chunk(void);
	~Chunk(void);

	void init(SDL_Renderer*, std::string);
	
    std::HashMap<int, Tile*> getTiles(void);

private:
    std::HashMap<int, Tile*> tiles;
};