#pragma once

#ifdef __APPLE__
	#include <SDL2_mixer/SDL_mixer.h>
#else
	#include "SDL_mixer.h"
#endif

#include <cstdio>
#include <algorithm>
#include <string>
#include <sstream>
#include <iostream>

#include "Defines.h"
#include "Tile.h"
#include "EntityPlayer.h"
#include "Renderer.h"
#include "Chunk.h"
#include "CollisionHandler.h"
#include "ChunkUtility.h"

#ifndef GAME_H
#define GAME_H

class Game
{
public:
	
	Game();
    
	~Game();
	
	enum APP_STATE {
		APP_OK = 0,
		APP_FAILED = 1
	};
	
	int init(void);
	void destroy(void);
    
	int run(void);
    
	void onEvent(SDL_Event* ev);
	void render(void);
	void collision(void);

	//std::pair<Chunk*, Vec2> getChunk(Vec2* Vec2);

	//std::pair<Tile*, Vec2> getTile(std::HashMap<Vec2, Tile*> tiles, Vec2* Vec2);
    
    //std::vector<std::pair<Tile*, Vec2> > getSurroundingTiles(int radius, Vec2* centerPos);
private:
    std::HashMap<Vec2, Chunk*> chunks;
	EntityPlayer* player;
	bool _running;

	Renderer* renderer;
	Mix_Chunk* music;
};

#endif
