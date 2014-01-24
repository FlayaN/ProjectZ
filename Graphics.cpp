#include "Graphics.h"

Graphics::Graphics(void)
{
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);	// specify OpenGL version
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);	// 3.2
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	win = SDL_CreateWindow("Project Z", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Settings::Graphics::screenWidth, Settings::Graphics::screenHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);	// create window
	renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		
	
	

	
    
    

	SDL_GL_SetSwapInterval(1);	// Vsync
		
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();	// init Glew (OpenGL extensions)
		
	if(err != GLEW_OK)
		std::cout << "Error: " << glewGetErrorString(err) << std::endl;
		
	std::cout << "Using GLEW: " << glewGetString(GLEW_VERSION) << std::endl;
	std::cout << "Using OpenGL: " << (char*)glGetString(GL_VERSION) << std::endl;

    
    context = SDL_GL_CreateContext(win);
    SDL_GL_MakeCurrent(win, context);
    
	printError("Graphics|Graphics");
}

Graphics& Graphics::getInstance(void)
{
	static Graphics instance;
	return instance;
}

SDL_Window* Graphics::getWindow(void)
{
	return win;
}

SDL_Renderer* Graphics::getRenderer(void)
{
	return renderer;
}

SDL_GLContext Graphics::getContext(void)
{
	return context;
}