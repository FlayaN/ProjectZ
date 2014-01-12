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
#include "TextureManager.h"
#include "Network.h"
#include "Settings.h"
#include "PerlinNoise.h"

#ifndef GAME_H
#define GAME_H

class Game
{
public:
	
	Game();
    
	~Game();
	
	enum APP_STATE
	{
		APP_OK = 0,
		APP_FAILED = 1
	};
	
	int init(void);
    
	int run(void);
    
	void onEvent(SDL_Event* ev);
	void render(void);
	void collision(void);

	void loadJson(void);

private:
    std::HashMap<glm::ivec2, Chunk*> chunks;
	std::vector<PlayerMP*> players;
	EntityPlayer* player;
	bool _running;

	Renderer* renderer;
	Mix_Chunk* music;

	bool online;
	Network* net;
	Camera* cam;
};

#endif
