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
#include <memory>

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
    std::HashMap<glm::ivec2, std::shared_ptr<Chunk> > chunks;
	std::vector<std::shared_ptr<PlayerMP> > players;
	std::shared_ptr<Camera> cam;
	std::shared_ptr<EntityPlayer> player;

	std::unique_ptr<Renderer> renderer;
	std::unique_ptr<Network> net;

	std::vector<TypeTile> tileTypes;
	TypePlayer playerType;
	
	SDL_Surface ct;
	Mix_Chunk* music;

	bool _running;
	bool online;
	int state;
};

#endif