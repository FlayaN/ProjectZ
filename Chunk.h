#pragma once


#include <unordered_map>
#include <string>

#include "Defines.h"
#include "Tile.h"

using namespace std::tr1;
class Chunk
{
public:
	Chunk(void);
	~Chunk(void);

	void init(SDL_Renderer*, std::string);
	
	HashMap<int, Tile*> getTiles(void);

private:
	HashMap<int, Tile*> tiles;
};

