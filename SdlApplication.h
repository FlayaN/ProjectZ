#ifdef __APPLE__
    #include <SDL2/SDL.h>
#else
    #include "SDL.h"
#endif

#include <cstdio>
#include "Tile.h"
#include <algorithm>

#ifndef Project_Z_SdlApplication_h
#define Project_Z_SdlApplication_h

class SdlApplication
{
public:
	
    SdlApplication() : _running(false)
    {
        
        //std::fill_n(tiles, 100, nullptr);
        
        
        tiles[5][5] = new Tile(renderer);
    }
    
    ~SdlApplication()
    {
        destroy();
    }
	
	enum APP_STATE
	{
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
	bool _running;
	SDL_Window *win;
	SDL_Renderer *renderer;
};


#endif
