#pragma once

#ifdef __APPLE__
	#include <SDL2/SDL.h>
	#include <SDL2_image/SDL_image.h>
#else
	#include "SDL.h"
	#include "SDL_image.h"

	
#endif

#include "Defines.h"
#include <iostream>

#include "GL_utilities.h"

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

		//SDL_CreateWindowAndRenderer(800, 600, SDL_WINDOW_OPENGL, &win, &renderer);


		win = SDL_CreateWindow("Project Z", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);	// create window
		renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		
		context = SDL_GL_CreateContext(win);
		SDL_GL_MakeCurrent(win, context);

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);	// specify OpenGL version
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);	// 3.2
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

		SDL_GL_SetSwapInterval(1);	// Vsync
		
		glewExperimental = GL_TRUE;
		GLenum err = glewInit();	// init Glew (OpenGL extensions)
		
		if(err != GLEW_OK)
			std::cout << "Error: " << glewGetErrorString(err) << std::endl;
		
		std::cout << "Using GLEW: " << glewGetString(GLEW_VERSION) << std::endl;
		std::cout << "Using OpenGL: " << (char*)glGetString(GL_VERSION) << std::endl;

		//glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

		printError("Graphics|Graphics");
	}

	Graphics(Graphics const&);
	Graphics &operator=(Graphics const&);
	~Graphics(){}
	
	SDL_Window* win;
	SDL_Renderer* renderer;
	SDL_GLContext context;
};

#endif