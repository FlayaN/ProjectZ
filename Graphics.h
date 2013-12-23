#pragma once

#ifdef __APPLE__
	#include <SDL2/SDL.h>
	#include <SDL2_image/SDL_image.h>
#else
	#include "SDL.h"
	#include "SDL_image.h"
#endif

#include "Defines.h"

#ifndef GRAPHICS_H
#define GRAPHICS_H
class Graphics
{
public:
	static Graphics& getInstance(void)
	{
		static Graphics instance;
		return instance;
	}

	SDL_Window* getWindow(void)
	{
		return win;
	}

	SDL_Renderer* getRenderer(void)
	{
		return renderer;
	}
private:
	Graphics(void)
	{
		win = SDL_CreateWindow("Project Z", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	}
	Graphics(Graphics const&);
	Graphics &operator=(Graphics const&);
	~Graphics(){}
	
	SDL_Window* win;
	SDL_Renderer* renderer;
};

#endif