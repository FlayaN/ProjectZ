#ifdef __APPLE__
    #include <SDL2/SDL.h>
#else
    #include "SDL.h"
#endif

#include <cstdio>
#include "Tile.h"
#include "EntityPlayer.h"
#include "Renderer.h"
#include <algorithm>
#include <string>

#ifndef Project_Z_Game_h
#define Project_Z_Game_h

class Game
{
public:
	
	Game() : _running(false) {
		
	}
    
	~Game() {
        destroy();
    }
	
	enum APP_STATE {
		APP_OK = 0,
		APP_FAILED = 1
	};
	
	int init(int width, int height);
	void destroy();
    
	int run(int width, int height);
    
	void onEvent(SDL_Event* ev);
	void Render();
	
private:
	Tile* tiles[10][10];
	EntityPlayer* player;
	bool _running;
	SDL_Window *win;
	Renderer* renderer;
};


#endif
