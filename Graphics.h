#pragma once

#ifdef __APPLE__
	#include <SDL2/SDL.h>
	#include <SDL2_image/SDL_image.h>
#else
	#include "SDL.h"
	#include "SDL_image.h"

	#define NO_SDL_GLEXT
	#include <GL/glew.h>
	#include <SDL_opengl.h>
#endif

#include "Defines.h"
#include <iostream>

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

	SDL_GLContext getContext(void)
	{
		return context;
	}
private:
	Graphics(void)
	{
		win = SDL_CreateWindow("Project Z", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		/*
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

		context = SDL_GL_CreateContext(win);

		SDL_GL_SetSwapInterval(1);

		std::cout << (char*)glGetString(GL_VERSION) << std::endl;*/
	}
	Graphics(Graphics const&);
	Graphics &operator=(Graphics const&);
	~Graphics(){}
	
	SDL_Window* win;
	SDL_Renderer* renderer;
	SDL_GLContext context;
};

#endif