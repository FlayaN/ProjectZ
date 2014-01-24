#ifndef GAME_H
#define GAME_H

#ifdef __APPLE__
	#include <SDL2_mixer/SDL_mixer.h>
    #include <dirent.h>
#else
	#include "SDL_mixer.h"
    #include "dirent.h"
#endif

#include <cstdio>
#include <algorithm>
#include <string>
#include <sstream>
#include <iostream>
#include <memory>


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
#include "TypeClothing.h"
#include "TypeConsumable.h"
#include "TypeMaterial.h"
#include "TypeWeapon.h"
#include "Chat.h"
#include "Utility.h"

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
	//void chat(SDL_Event* ev, const Uint8* keystates);
	void render(void);
	void collision(void);

	void loadJson(void);
	void loadSettings(void);
	void loadTiles(void);
	void loadItems(void);

	void combineTileTextures(void);
	void combineItemTextures(void);
private:
    std::HashMap<glm::ivec2, std::shared_ptr<Chunk> > chunks;
	std::vector<std::shared_ptr<PlayerMP> > players;
	std::shared_ptr<Camera> cam;
	std::shared_ptr<EntityPlayer> player;
	std::shared_ptr<Network> net;

	std::unique_ptr<Renderer> renderer;
	
	std::vector<TypeTile> tileTypes;
	std::vector<std::shared_ptr<TypeItem> > itemTypes;

	std::shared_ptr<Chat> chat;

	TypePlayer playerType;
	
	SDL_Surface tileTexture;
	SDL_Surface itemTexture;

	Mix_Chunk* music;

	bool _running;
	bool online;
	bool keyFocus;
	int state;

	//std::string tmpChat;
	char buff[1400];
};

#endif