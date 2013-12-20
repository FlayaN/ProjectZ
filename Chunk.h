#pragma once


#include <unordered_map>
#include <string>

#include "Defines.h"
#include "Tile.h"

class Chunk
{
public:
	Chunk(Vec2* coord);
	~Chunk(void);

	void init(SDL_Renderer*, std::string);
	
    std::HashMap<Vec2, Tile*> getTiles(void);
    
    Vec2* getCoord(void);

private:
    std::HashMap<Vec2, Tile*> tiles;
    
    Vec2* coord;
};