#ifndef GAME_H
#define GAME_H

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

#include "dirent.h"
#include "lib/rapidjson/document.h"
#include "lib/rapidjson/filestream.h"

#include "Defines.h"
#include "Tile.h"
#include "EntityPlayer.h"
#include "Renderer.h"
#include "Chunk.h"
#include "CollisionHandler.h"
#include "ChunkUtility.h"
#include "Network.h"
#include "Settings.h"
#include "PerlinNoise.h"
#include "TypeTile.h"
#include "TypePlayer.h"
#include "Settings.h"
#include "SimplexNoise.h"

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
	
	int run(void);
    
	void onEvent(SDL_Event* ev);
	void render(void);
	void collision(void);

	void loadJson(void);
	void loadTiles(void);

	void combineTileTextures(void);

private:
    std::HashMap<glm::ivec2, Chunk*> chunks;
	std::vector<PlayerMP*> players;
	EntityPlayer* player;

	std::vector<TypeTile> tileTypes;
	TypePlayer playerType;
	SDL_Surface ct;

	bool _running;

	Renderer* renderer;
	Mix_Chunk* music;

	bool online;
	Network* net;
	Camera* cam;
	int state;
};

#endif
