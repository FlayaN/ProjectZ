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
#include <regex>

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
#include "Settings.h"
#include "SimplexNoise.h"
#include "Chat.h"
#include "Utility.h"
#include "Json.h"

class Game
{
public:
	Game(std::shared_ptr<Json>, std::string, std::shared_ptr<Graphic>);
	~Game(void);
	void onEvent(SDL_Event*, const Uint8*);
	bool isRunning(void);
	void update(float, const Uint8*);
	void render(void);
	void collision(void);
	bool hasNewState(void);
	STATE requestStateChange(void);
private:
	std::HashMap<glm::ivec2, std::shared_ptr<Chunk> > chunks;
	std::vector<std::shared_ptr<PlayerMP> > players;

	std::shared_ptr<Camera> cam;
	std::shared_ptr<EntityPlayer> player;
	std::shared_ptr<Network> net;
	std::shared_ptr<Chat> chat;
	std::shared_ptr<Json> json;
    std::shared_ptr<Graphic> graphic;

	std::unique_ptr<Renderer> renderer;

	Mix_Chunk* music;

	bool running;
	bool online;
	bool keyFocus;

	float tmpTime;

	bool newState;
	STATE state;
};

#endif