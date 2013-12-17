#ifdef __APPLE__
    #include <SDL2/SDL.h>
#else
    #include "SDL.h"
#endif

#include "Defines.h"
#include "Tile.h"
#include "EntityPlayer.h"
#include "Renderer.h"
#include "Chunk.h"
#include "CollisionHandler.h"

#include <cstdio>
#include <algorithm>
#include <string>
#include <sstream>
#include <iostream>
#include <utility>

#ifndef Project_Z_Game_h
#define Project_Z_Game_h

class Game
{
public:
	
	Game();
    
	~Game();
	
	enum APP_STATE {
		APP_OK = 0,
		APP_FAILED = 1
	};
	
	int init(int width, int height);
	void destroy();
    
	int run(int width, int height);
    
	void onEvent(SDL_Event* ev);
	void render(void);
	void collision(void);

	std::pair<Chunk*, Vec2> getChunk(Vec3* coord);

	std::pair<Tile*, Vec2> getTile(std::HashMap<Coord, Tile*> tiles, Vec3* coord);
	
private:
    std::HashMap<Coord, Chunk*> chunks;
	EntityPlayer* player;
	bool _running;
	SDL_Window *win;
	Renderer* renderer;
};


#endif
