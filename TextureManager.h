#pragma once

#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

#include "libraries\pugixml.hpp"
#include "Graphics.h"
#include "Defines.h"

class TextureManager
{
public:
	static TextureManager& getInstance(void)
	{
		static TextureManager instance;
		return instance;
	}

	SDL_Texture* getTexture(std::string id);

private:
	void init(void);

	TextureManager(void);
	TextureManager(TextureManager const&);
	TextureManager &operator=(TextureManager const&);
	~TextureManager(){}


	std::HashMap<std::string, SDL_Texture*> textures;
	//std::vector<SDL_Texture*> textures;
};

#endif