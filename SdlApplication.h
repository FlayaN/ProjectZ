#ifdef __APPLE__
    #include <SDL2/SDL.h>
#else
    #include "SDL.h"
#endif

#include <cstdio>

#ifndef Project_Z_SdlApplication_h
#define Project_Z_SdlApplication_h

class SdlApplication
{
public:
	
    SdlApplication() : _running(false)
    {
        
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
	bool _running;
	SDL_Window *win;
	SDL_Renderer *renderer;
};


#endif
