#pragma once

#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include "lib/rapidjson/document.h"
#include "lib/rapidjson/filestream.h"
//#include "rapidjson/rapidjson.h"

#ifdef __APPLE__
    #include <CoreFoundation/CoreFoundation.h>
#endif
#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <stdio.h>

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

	void init(const rapidjson::Value&);

	SDL_Surface* getSurface(std::string id);

private:

	TextureManager(void);
	TextureManager(TextureManager const&);
	TextureManager &operator=(TextureManager const&);
	~TextureManager(){}


	std::HashMap<std::string, SDL_Surface*> surfaces;
};

#endif